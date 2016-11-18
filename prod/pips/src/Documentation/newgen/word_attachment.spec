--NEWGEN-START 90
import call from "ri.newgen";
import entity from "ri.newgen";
import loop from "ri.newgen";
import reference from "ri.newgen";
external void_star;
attachee = statement_line_number:int + persistant reference:reference + persistant call:call + persistant declaration:entity + type:string + persistant loop:loop + persistant module_head:entity + complementary_sections:unit + complexities:unit + continuation_conditions:unit + cumulated_effects:unit + out_regions:unit + preconditions:unit + privatized_regions:unit + proper_effects:unit + proper_regions:unit + regions:unit + static_control:unit + transformers:unit + decoration:unit + comment:unit;
attachment = attachee:attachee x begin:int x end:int;
attachments = attachment:attachment*;
word_to_attachments = word_pointer:void_star -> attachments:attachments;
