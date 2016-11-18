--NEWGEN-START 97
import reference from "ri.newgen";
import preference from "ri.newgen";
import entity from "ri.newgen";
import statement from "ri.newgen";
pstatement_reductions = persistant statement:statement -> reductions:reductions;
reduction_operator = none:unit + min:unit + max:unit + sum:unit + csum:unit + prod:unit + and:unit + or:unit + bitwise_and:unit + bitwise_or:unit + bitwise_xor:unit + eqv:unit + neqv:unit;
reduction = reference:reference x op:reduction_operator x dependences:entity* x trusted:preference*;
reductions = list:reduction*;
