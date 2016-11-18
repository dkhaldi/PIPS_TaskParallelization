--NEWGEN-START 7
database = name:string x directory:string x resources:resource*;
resource = name:string x owner_name:string x status:status x time:int x file_time:int;
status = memory:string + file:string;
