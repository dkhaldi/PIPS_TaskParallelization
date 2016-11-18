--NEWGEN-START 161
import statement from "ri.newgen";
external Ppolynome;
complexity = eval:Ppolynome x varcount:varcount x rangecount:rangecount x ifcount:ifcount;
ifcount = profiled:int x computed:int x halfhalf:int;
rangecount = profiled:int x guessed:int x bounded:int x unknown:int;
varcount = symbolic:int x guessed:int x bounded:int x unknown:int;
