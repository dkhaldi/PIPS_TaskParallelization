--NEWGEN-START 15
makefile = rules:rule* x active_phases:string*;
owner = program:unit + module:unit + main:unit + callees:unit + callers:unit + all:unit + select:unit + compilation_unit:unit;
real_resource = resource_name:string x owner_name:string;
rule = phase:string x required:virtual_resource* x produced:virtual_resource* x preserved:virtual_resource* x modified:virtual_resource* x pre_transformation:virtual_resource* x post_transformation:virtual_resource*;
virtual_resource = name:string x owner:owner;
