--NEWGEN-START 167
import entity from "ri.newgen";
import expression from "ri.newgen";
alias_associations = list:alias_association*;
alias_association = variable:entity x section:entity x offset:expression x lower_offset:int x upper_offset:int x call_chain:call_site*;
call_site = function:entity x ordering:int;
dynamic_check = first:entity x second:entity x checked:bool;
