#! /usr/bin/env python

import sys
import re

usage= "usage: pipsmakerc2python.py rc-file.tex properties.rc pipsdep.rc [-loop|-module|-modules|-properties]"

if len(sys.argv) < 5:
	print usage
	exit(1)

texfile = sys.argv[1]
generator = sys.argv[4]

#Read propdep file and convert it into a map.
input = open(sys.argv[3],"r")
lines = input.readlines()
input.close()

pipsdep= dict()
for line in lines:
	m = re.match(r"(.*?):\s*(.*)", line)
	p = m.group(1)
	deps = []
	if m.lastindex == 2:
		deps = re.split(" ", m.group(2))
		deps = deps[0:len(deps)-1]
	deps = map(lambda x: x.lower(), deps)
	pipsdep[p] = deps

#Read properties into a string
rcfile = sys.argv[2]
input = open(rcfile,"r")
lines = input.readlines()
input.close()

pipsprops = dict()
for line in lines:
	m = re.match("\s*(.*?)\s+(.*)", line)
	d = m.group(2)
	if d == "TRUE": d = "True"
	if d == "FALSE" : d = "False"
	pipsprops[m.group(1)] = d

#Read input tex file into a string
input = open(texfile,"r")
lines = input.readlines()
rc = "".join(lines)
input.close()


def printPythonMethod(name,doc):
	extraparamsetter = ""
	extraparamresetter = ""
	extraparams = ""
	has_loop_label = False

	if name in pipsdep and len(pipsdep[name]) > 0:
		props = []
		for prop in pipsdep[name]:
			short_prop = re.sub(r'^' + name + '\_(.*)', r'\1', prop)
			arg = short_prop + "=None" # + pipsprops[prop.upper()]

			if prop == "loop_label":
				has_loop_label = True;
				extraparamsetter += '\tif self.workspace:self.workspace.cpypips.push_property("LOOP_LABEL",pypsutils.formatprop(self.label))\n'
				extraparamresetter = '\t\tif self.workspace:self.workspace.cpypips.pop_property("LOOP_LABEL")\n'  + extraparamresetter
			else:
				props.append(arg)
				extraparamsetter += '\tif '+short_prop+' == None and self.workspace:'+short_prop+'=self.workspace.props.'+prop + '\n'
				extraparamsetter += '\tif self.workspace:self.workspace.cpypips.push_property("%s",pypsutils.formatprop(%s))\n' % ( prop.upper(), short_prop)
				extraparamresetter = '\t\tif self.workspace:self.workspace.cpypips.pop_property("%s")\n' % (prop.upper()) + extraparamresetter

		if len(props) > 0:
			extraparams = ",".join(props) + ","
	
	#Some regexp to filter the LaTeX source file, sometimes they work, sometimes they don't,
	#sometimes it's worth than before but they only act one the produced Python comments
	doc = re.sub(r'(?ms)(\\begin\{.*?\})|(\\end\{.*?\})|(\\label\{.*?\})','',doc)  #Remove any begin,end and label LaTeX command
	doc = re.sub(r'(?ms)(\\(.*?)\{.*?\})', r'', doc)#, flags=re.M|re.S) #Remove any other LaTeX command
	doc = doc.replace("\_","_") #Convert \_ occurences to _
	doc = doc.replace("~"," ")  #Convert ~ to spaces
	doc = re.sub(r"\\verb\|(.*?)\|", r"\1", doc)#, flags=re.M|re.S) #Replace \verb|somefile| by somefile
	doc = re.sub(r"\\verb\/(.*?)\/", r"\1", doc)#, flags=re.M|re.S) #Replace \verb/something/ by something
	doc = re.sub(r"\\verb\+(.*?)\+", r"\1", doc)#, flags=re.M|re.S) #Replace \verb+something+ by something
	doc = doc.replace("\PIPS{}","PIPS") #Convert \PIPS{} to PIPS
	name = re.sub(r'\s',r'_',name)

	mself = "self"
	if has_loop_label and generator == "-loop":
		mself = "self.module"
	
	if (has_loop_label and generator == "-loop") or (not has_loop_label and generator != "-loop"):
		if generator == "-modules":
			extraparams = extraparams + " concurrent=False,"

		print '\ndef '+name+'(self,'+extraparams+' **props):'
		print '\t"""'+doc+'"""'
		print extraparamsetter
		print '\tif '+mself+'.workspace: old_props = pypsutils.set_properties(self.workspace,pypsutils.update_props("'+name.upper()+'",props))'

		print '\ttry:'
		if generator != "-modules":
			print '\t\tpypsutils.apply('+mself+',\"'+name+'\")'
		else:
			print '\t\tif concurrent: pypsutils.capply(self,\"'+name+'\")'
			print '\t\telse:'
			print '\t\t\tfor m in self: pypsutils.apply(m,\"'+name+'\")'
		print '\texcept:'
		print '\t\traise'
		print '\tfinally:'
		print '\t\tif '+mself+'.workspace: pypsutils.set_properties('+mself+'.workspace,old_props)'
		print '\n' + extraparamresetter
		print generator[1:] + "." + name + "=" + name

#Print workspace properties
if generator == "-properties":
	del pipsprops[""]
	sys.stdout.write("workspace.Props.all=dict({")
	sys.stdout.write(",".join(map(lambda (key,val) : "'"+key+"': "+val,pipsprops.iteritems())))
	sys.stdout.write("})")
	exit(0)

#Parse string documentation
doc_strings= re.findall(r'\\begin\{PipsPass\}(.*?)\\end\{PipsPass\}', rc, flags=re.M | re.S)

for dstr in doc_strings:
	m = re.match(r'\{([^\}]+)\}[\n]+(.*)', dstr, flags = re.M | re.S)
	printPythonMethod(m.group(1), m.group(2))

