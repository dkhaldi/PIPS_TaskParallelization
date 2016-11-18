--NEWGEN-START 151
import reference from "ri.newgen";
import action from "ri.newgen";
external Pvecteur;
bound_pair = index:int x lb:Pvecteur x ub:Pvecteur;
comp_desc = persistant reference:reference x action:action x section:comp_sec;
comp_desc_set = comp_descs:comp_desc*;
comp_sec = hull:simple_section x complements:simple_section*;
context_info = line:int x rank:int x nest:int;
dad_struct = rtemps:ref_temp* x shape:bound_pair*;
ref_temp = index:int x rtype:rtype;
rtype = nonlinear:unit + linvariant:unit + lininvariant:unit;
simple_section = context:context_info x dad:dad_struct;
