--NEWGEN-START 206
import entity from "ri.newgen";
import expression from "ri.newgen";
import effect from "effects.newgen";
import statement from "ri.newgen";
map_effect_bool = persistant effect:effect -> bool:bool;
map_effect_step_point = persistant effect:effect -> step_point:step_point;
map_entity_int = entity:entity -> int:int;
step_clause = reduction:map_entity_int + private:entity* + shared:entity* + transformation:int + nowait:unit + threadprivate:entity* + copyin:entity* + firstprivate:entity* + schedule:string*;
step_comm = path:map_effect_step_point x interlaced:map_effect_bool x partial:map_effect_bool;
step_directives = persistant statement:statement -> step_directive:step_directive;
step_directive = type:int x persistant block:statement x clauses:step_clause*;
step_point = module:entity x persistant stmt:statement x persistant data:effect;
