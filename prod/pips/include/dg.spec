--NEWGEN-START 221
import statement from "ri.newgen";
import effect from "effects.newgen";
import vertex from "graph.newgen";
external Ptsg;
cone = levels:int* x generating_system:Ptsg;
conflict = persistant source:effect x persistant sink:effect x cone:cone;
dg_arc_label = conflicts:conflict*;
dg_vertex_label = statement:int x sccflags:sccflags;
sccflags = enclosing_scc:scc x mark:int x dfnumber:int x lowlink:int;
sccs = sccs:scc*;
scc = vertices:vertex* x indegree:int;
