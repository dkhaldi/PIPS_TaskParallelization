--NEWGEN-START 115
import entity from "ri.newgen";
import expression from "ri.newgen";
align = alignment:alignment* x template:entity;
alignment = arraydim:int x templatedim:int x rate:expression x constant:expression;
distribute = distribution:distribution* x processors:entity;
distribution = style:style x parameter:expression;
style = none:unit + block:unit + cyclic:unit;
