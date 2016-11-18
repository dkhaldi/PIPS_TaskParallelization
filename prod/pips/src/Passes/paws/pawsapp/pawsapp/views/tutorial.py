# -*- coding: utf-8 -*-

"""
Generic tutorial controller

"""
import os, re, pickle
from collections  import OrderedDict
from ConfigParser import SafeConfigParser
from subprocess   import Popen, PIPE

from pyramid.view import view_config
from pyramid.httpexceptions import HTTPFound

from .detector    import detect_language
from .operations  import get_workdir, get_resultdir
from .graph       import create_graph_images
from ..utils      import extractFirstComment, htmlHighlight


_paws_marker      = '<END OF THE STEP>'


def get_tutorialdir(request, tut):
    """Get tutorial directory full path.

    :request: Pyramid request
    :tut:     Tutorial name
    """
    return os.path.join(request.registry.settings['paws.validation'], 'tutorials', os.path.basename(tut))


def get_info(request, tut):
    """Get information about the tutorial from the 'info.ini' file.

    :request:  Pyramid request
    :tutorial: Tutorial name
    """
    cfg = SafeConfigParser()
    cfg.optionxform = str # case-sensitive keys
    cfg.read(os.path.join(get_tutorialdir(request, tut), 'info.ini'))

    info = { 'title'  : cfg.get('info', 'title'),
             'descr'  : cfg.get('info', 'description'),
             'source' : cfg.get('info', 'source'),
             }
    return info


re_display = re.compile(r'\s*display')
re_graph   = re.compile(r'\s*apply PRINT_DOT_DEPENDENCE_GRAPH\s*\[(\w+)\]')

def parse_tpips(tpips):
    """Split tpips file into individual steps
    """
    ops    = OrderedDict()
    graphs = {}
    index  = 1
    for line in file(tpips):
        if index not in ops:
            ops[index] = ''
        ops[index] += line
        m = re_graph.match(line)
        if m:
            graphs[index] = m.group(1)
        if re_display.match(line) or re_graph.match(line):
            index += 1
    return ops, graphs


@view_config(route_name='tutorial_init', renderer='pawsapp:templates/lib/tutorial_paginator.mako', permission='view')
def tutorial_init(request):
    """Initialize tutorial
    """
    tutname = os.path.basename(request.matchdict['tutorial'])  # sanitized
    info    = get_info(request, tutname)
    tutdir  = get_tutorialdir(request, tutname)
    dirname = get_workdir(request, reuse=False) # return value not used
    resdir  = get_resultdir(request)

    code    = request.POST['code']
    tpips   = os.path.join(tutdir, '%s.tpips' % tutname)
    lang    = detect_language(code)

    ops, graphs = parse_tpips(tpips)

    # Source code (in result dir)
    file(os.path.join(resdir, info['source']), 'w').write(code)

    # Full tpips script, with end-of-step markers
    full_tpips = os.path.join(resdir, 'full-markers.tpips')
    file(full_tpips, 'w').write(('echo %s\n' % _paws_marker).join(ops.values()))

    # Step-by-step tpips chunks (in result dir)
    for k,v in ops.items():
        step_tpips = os.path.join(resdir, 'step-%d.tpips' % k)
        file(step_tpips, 'w').write(v)

    # Execute full tpips script
    p = Popen(['tpips', full_tpips, '1'], stdout=PIPE, stderr=PIPE)
    p.wait()

    # Split results along markers and save to file
    results  = p.communicate()[0].split(_paws_marker)[:-1]
    images   = {}
    comments = []
    for i in range(len(results)):
        step_result = os.path.join(resdir, 'step-%d.txt' % (i+1))
        file(step_result, 'w').write(results[i])
        comments.append(extractFirstComment(results[i], lang))
    pickle.dump(comments, file(os.path.join(resdir, 'comments.pickle'), 'w'))

    for index in graphs:
        images[index] = create_graph_images(request, [graphs[index]], db=tutname + '.database')
    pickle.dump(images, file(os.path.join(resdir, 'images.pickle'), 'w'))

    request.session['nb_steps'] = len(results)
    request.session['lang']     = lang

    return dict(step     = 0,
                nb_steps = len(results),
                lang     = lang,
                name     = tutname,
                comments = comments,
                )


@view_config(route_name='tutorial', renderer='pawsapp:templates/tutorial.mako', permission='view')
def tutorial(request):
    """
    """
    form        = request.params
    step        = int(form.get('step', 0))
    initialized = bool(form.get('initialized', False))

    tutname = os.path.basename(request.matchdict['tutorial'])  # sanitized
    info    = get_info(request, tutname)
    tutdir  = get_tutorialdir(request, tutname)
    dirname = get_workdir(request, reuse= (step!=0 or initialized)) # return value not used
    resdir  = get_resultdir(request)

    comments = pickle.load(file(os.path.join(resdir, 'comments.pickle'))) if initialized else []

    if step == 0:

        source  = os.path.join(resdir if initialized else tutdir, os.path.basename(info['title']))
        tpips   = os.path.join(tutdir, '%s.tpips' % tutname)
        return dict(tutorial = tutname,
                    initialized = initialized,
                    step     = step,
                    nb_steps = request.session.get('nb_steps', 0),
                    lang     = '',
                    name     = tutname,
                    info     = info,
                    source   = file(source).read(),
                    tpips    = htmlHighlight(re.sub("(echo.*\n)", "", file(tpips).read()), "C"),
                    comments = comments,
                    )

    else:

        # Check if environment is initialized correctly:
        if not 'lang' in request.session: ##TODO: better checks
            request.session.flash(u'Tutorial not initialized correctly - restarting')
            return HTTPFound(location=request.route_url(request.matched_route.name, tutorial=tutname))

        step_result = os.path.join(resdir, 'step-%d.txt' % step)
        step_tpips  = os.path.join(resdir, 'step-%d.tpips' % step)
        comments    = pickle.load(file(os.path.join(resdir, 'comments.pickle')))
        images      = pickle.load(file(os.path.join(resdir, 'images.pickle')))
        lang        = request.session['lang']

        return dict(tutorial = tutname,
                    step     = step,
                    nb_steps = request.session['nb_steps'],
                    lang     = lang,
                    name     = tutname,
                    info     = info,
                    source   = htmlHighlight(file(step_result).read(), lang),
                    tpips    = htmlHighlight(re.sub("(echo.*\n)", "", file(step_tpips).read()), 'C'),
                    comments = comments,
                    images   = images.get(step, {}),
                    )
        
        
