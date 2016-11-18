--NEWGEN-START 214
import entity from "ri.newgen";
import effect from "effects.newgen";
entity_task_buffers = entity:entity -> task_buffers:task_buffers;
sesam_buffers_processing_context = kernel_tasks:entity{} x server_tasks:entity{} x kernel_buffers:entity_task_buffers x server_buffers:entity_task_buffers x buffers:entity{};
task_buffers = input:entity{} x output:entity{};
