--NEWGEN-START 105
import entity from "ri.newgen";
import constant from "ri.newgen";
atom = equivar:entity x equioff:int;
chain = atoms:atom*;
data = datavars:datavar* x datavals:dataval*;
dataval = constant:constant x nboccurrences:int;
datavar = variable:entity x nbelements:int;
equivalences = chains:chain*;
