--NEWGEN-START 20
external db_void;
db_owned_resources = db_symbol:db_symbol -> db_resource:db_resource;
db_resource = pointer:db_void x db_status:db_status x time:int x file_time:int;
db_resources = db_symbol:db_symbol -> db_owned_resources:db_owned_resources;
db_status = loaded:unit + stored:unit + required:unit + loaded_and_stored:unit;
tabulated db_symbol = name:string;
