--NEWGEN-START 101
import expression from "ri.newgen";
import entity from "ri.newgen";
gexpression = guard:expression x expression:expression;
pattern = variable:entity x condition:expression x parameter:expression x operator:entity x indices:entity*;
reduced_loops = ordering:int*;
sexpression = gexpressions:gexpression*;
