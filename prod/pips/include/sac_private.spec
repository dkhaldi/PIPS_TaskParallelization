--NEWGEN-START 174
import entity from "ri.newgen";
import expression from "ri.newgen";
import statement from "ri.newgen";
import reference from "ri.newgen";
import reduction from "reductions_private.newgen";
external operator_id_sons;
matchTree = patterns:patternx* x sons:matchTreeSons;
matchTreeSons = int:int -> matchTree:matchTree;
match = type:opcodeClass x args:expression*;
opcode = name:string x vectorSize:int x argType:int* x cost:float;
operator_id_tree = id:int x sons:operator_id_sons;
patternArg = static:int + dynamic:unit;
patternx = class:opcodeClass x args:patternArg*;
reductionInfo = persistant reduction:reduction x count:int x persistant vector:entity;
simdstatement = opcode:opcode x nbArgs:int x vectors:entity[16] x arguments:expression[48];
tabulated opcodeClass = name:string x nbArgs:int x opcodes:opcode*;
transformation = name:string x vectorLengthOut:int x subwordSizeOut:int x vectorLengthIn:int x subwordSizeIn:int x nbArgs:int x mapping:int[16];
