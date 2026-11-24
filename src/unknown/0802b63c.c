typedef unsigned char u8;
typedef unsigned int u32;
struct TaskGroup;
struct UnitTaskContext { struct TaskGroup *group; void *backing; };
typedef void (*MemoryClear)(void *, u32);
extern struct UnitTaskContext *gUnitTaskContext;
extern MemoryClear gRuntimeClear;
extern void *AllocateGlobalPoolBytes(u32);
extern struct TaskGroup *InitializeTaskGroup(void *, u32);
extern void ExpandUnitTaskDataBlock(void *, const void *);
__asm__(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200f440\n.global gRuntimeClear\n.set gRuntimeClear,0x0836d4b8\n.global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes,0x08022841\n.global InitializeTaskGroup\n.thumb_set InitializeTaskGroup,0x08005c15\n.global ExpandUnitTaskDataBlock\n.thumb_set ExpandUnitTaskDataBlock,0x0800543d\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
/* Keep allocation snapshots distinct from the global context reloaded after helpers. */
void InitializeUnitTaskContext(u32 byte_count)
{
    u8 *allocation = AllocateGlobalPoolBytes(byte_count);
    struct TaskGroup *group;
    struct UnitTaskContext *context;
    gUnitTaskContext = (struct UnitTaskContext *)allocation;
    gRuntimeClear(allocation, 0x209c);
    gUnitTaskContext->backing = allocation;
    group = InitializeTaskGroup(allocation + 0x209c, byte_count - 0x209c);
    context = gUnitTaskContext;
    context->group = group;
    ExpandUnitTaskDataBlock((u8 *)context + 0x65c, (const void *)0x083be1f4);
}
