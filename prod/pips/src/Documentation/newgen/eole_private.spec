--NEWGEN-START 124
import expression from "ri.newgen";
import entity from "ri.newgen";
assignment = lhs:function x rhs:function x dependences:entity*;
expressionwithlevel = level:entity* x expression:expression;
function = op:entity x args:entity*;
lexpressionwithlevel = list:expressionwithlevel*;
persistant_expression_to_entity = persistant expression:expression -> entity:entity;
