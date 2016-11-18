--NEWGEN-START 10
external vertex_label;
external arc_label;
graph = vertices:vertex*;
successor = arc_label:arc_label x vertex:vertex;
vertex = vertex_label:vertex_label x successors:successor*;
