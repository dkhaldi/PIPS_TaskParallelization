--NEWGEN-START 171
import entity from "ri.newgen";
abc_checked = list:array_dimension_checked*;
array_dimension_checked = array:entity x dims:dimension_checked*;
dimension_checked = dim:int x lower:bool x upper:bool;
