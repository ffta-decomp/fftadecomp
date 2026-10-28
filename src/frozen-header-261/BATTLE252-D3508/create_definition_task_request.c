#include "../../task_tree_core.h"

struct TaskDefinition {
    TaskCallback callback;
    u16 payload_size;
    u16 selector_bits;
};
struct DefinitionTaskEvent {
    u32 unknown_at_00;
    void *owner;
    u32 argument;
    u32 flags;
    u32 unknown_at_10;
    u16 definition_id;
    u16 variant;
    u16 extra_id_bits;
    u16 unknown_at_1a;
};
typedef char DefinitionEventMustBe28Bytes[sizeof(struct DefinitionTaskEvent) == 28 ? 1 : -1];
extern const struct TaskDefinition StandardDefinitions[];
extern const struct TaskDefinition ExtendedDefinitions[];
extern u32 IsDefinitionUnitGateBlocked(void *context, u16 definition_id);
extern u32 HasRecordFlagBitThree(void *context);
extern void SpecialDefinitionTask(TaskNode *, u16 *, void *);
__asm__(".global StandardDefinitions\n.set StandardDefinitions, 0x083947d8\n"
        ".global ExtendedDefinitions\n.set ExtendedDefinitions, 0x08395280\n"
        ".global IsDefinitionUnitGateBlocked\n.thumb_set IsDefinitionUnitGateBlocked, 0x080d3b99\n"
        ".global HasRecordFlagBitThree\n.thumb_set HasRecordFlagBitThree, 0x080d3b39\n"
        ".global SpecialDefinitionTask\n.thumb_set SpecialDefinitionTask, 0x080e2399\n"
        ".global CreateTaskNode_08005954\n.thumb_set CreateTaskNode_08005954, 0x08005955");

TaskNode *CreateDefinitionTaskRequest(u16 definition_id, void *owner, u32 argument)
    __asm__("CoreStateDirect_000D3508");
TaskNode *CreateDefinitionTaskRequest(u16 definition_id, void *owner, u32 argument)
{
    struct DefinitionTaskEvent event;
    TaskCallback callback;
    u32 payload_size;
    u8 variant;
    TaskNode *created = 0;
    event.definition_id = definition_id;
    event.owner = owner;
    event.argument = argument;
    event.flags = 0;
    if (definition_id <= 0x155) {
        register const struct TaskDefinition *base __asm__("r1");
        register u32 index __asm__("r0");
        register const struct TaskDefinition *definition __asm__("r0");
        if ((u8)IsDefinitionUnitGateBlocked(owner, definition_id) != 0)
            event.flags = 2;
        variant = (u8)HasRecordFlagBitThree(owner);
        event.variant = variant;
        event.extra_id_bits = 0;
        /* The verified standard arm holds base in r1 and index in r0.
         * Branch-local bindings preserve those lifetimes with defined values. */
        base = StandardDefinitions;
        __asm__("" : "+r" (base));
        index = (u32)definition_id - 1;
        /* Keep the original named table and subtract-before-scale index.
         * Defined read/write index and read-only base emit no instructions. */
        __asm__("" : "+r" (index) : "r" (base));
        /* The final address reuses the offset register, offset first. */
        definition = (const struct TaskDefinition *)(index * 8 + (u32)base);
        __asm__("" : "+r" (definition));
        callback = definition->callback;
        payload_size = definition->payload_size;
    } else {
        register const struct TaskDefinition *base __asm__("r0");
        register u32 index __asm__("r1");
        register const struct TaskDefinition *definition __asm__("r1");
        /* The extended arm instead holds base in r0 and index in r1. */
        base = ExtendedDefinitions;
        __asm__("" : "+r" (base));
        index = (u32)definition_id - 0x156;
        __asm__("" : "+r" (index) : "r" (base));
        /* The final address reuses the offset register, offset first. */
        definition = (const struct TaskDefinition *)(index * 8 + (u32)base);
        __asm__("" : "+r" (definition));
        callback = definition->callback;
        payload_size = definition->payload_size;
        if (definition_id == 0x159) {
            if ((u8)IsDefinitionUnitGateBlocked(owner, (u16)argument) != 0)
                event.flags = 2;
            event.variant = StandardDefinitions[argument - 1].selector_bits;
            event.extra_id_bits = argument;
            callback = SpecialDefinitionTask;
            payload_size = 40;
        }
    }
    /* Preserve unwritten event bytes and the constructor's actual side effects. */
    created = CreateTaskNode_08005954(*(TaskGroup **)0x0200f430, callback,
                                     payload_size, (const u32 *)&event,
                                     *(TaskNode **)0x020159c0);
    return created;
}
