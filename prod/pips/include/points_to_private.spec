--NEWGEN-START 217
import descriptor from "ri.newgen";
import approximation from "ri.newgen";
import statement from "ri.newgen";
import cell from "effects.newgen";
points_to_graph = bottom:bool x set:points_to{};
points_to_list = bottom:bool x list:points_to*;
points_to = source:cell x sink:cell x approximation:approximation x descriptor:descriptor;
statement_points_to = persistant statement:statement -> points_to_list:points_to_list;
