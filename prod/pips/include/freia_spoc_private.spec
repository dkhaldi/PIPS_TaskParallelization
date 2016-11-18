--NEWGEN-START 120
import entity from "ri.newgen";
import statement from "ri.newgen";
dag = inputs:dagvtx* x outputs:dagvtx* x vertices:dagvtx*;
dagvtx = content:vtxcontent x succs:dagvtx*;
pstatement = persistant statement:statement + empty:unit;
vtxcontent = optype:int x opid:int x source:pstatement x inputs:entity* x out:entity;
