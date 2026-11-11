typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*MemoryClear)(void *, u32);
struct BattlePhaseContext { u8 unknown_00[68]; void *route; };
extern void ReleaseBattleRouteRecord(void *);
extern void *GetContentConsumerContext(void);
extern u32 CollectBattleUnitRecordAddresses(void *, u32 *);
extern void *DisposeBattleContentActor(void *);
extern void *ReleaseBattleActionRegistry(void *);
extern void ClearFirstWord(void *);
extern void *GetManagedWorkAllocator(void);
extern void ReleaseGlobalPoolAllocation(void *);
extern u32 ComputeBattleRecordPoolBytes(u32);
extern u32 BattleObjectIndexOffset(u8);
extern void ReleasePublishedBattleIndicator(void);
__asm__(".global ReleaseBattleRouteRecord\n.thumb_set ReleaseBattleRouteRecord, 0x0809d459\n"
        ".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext, 0x08096d7d\n"
        ".global CollectBattleUnitRecordAddresses\n.thumb_set CollectBattleUnitRecordAddresses, 0x08099cdd\n"
        ".global DisposeBattleContentActor\n.thumb_set DisposeBattleContentActor, 0x080995c1\n"
        ".global ReleaseBattleActionRegistry\n.thumb_set ReleaseBattleActionRegistry, 0x080993f5\n"
        ".global ClearFirstWord\n.thumb_set ClearFirstWord, 0x0800718d\n"
        ".global GetManagedWorkAllocator\n.thumb_set GetManagedWorkAllocator, 0x0808f77d\n"
        ".global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation, 0x08022855\n"
        ".global ComputeBattleRecordPoolBytes\n.thumb_set ComputeBattleRecordPoolBytes, 0x08022081\n"
        ".global BattleObjectIndexOffset\n.thumb_set BattleObjectIndexOffset, 0x0814913d\n"
        ".global ReleasePublishedBattleIndicator\n.thumb_set ReleasePublishedBattleIndicator, 0x080bd055\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");
void ReleasePublishedBattleRuntime(void) __asm__("CoreDependency29_00096CB8");
void ReleasePublishedBattleRuntime(void)
{
    register struct BattlePhaseContext **phase_cell __asm__("r4") =
        (struct BattlePhaseContext **)0x0200f4a8;
    u32 actor_addresses[13];
    s32 actor_count;
    register MemoryClear *clear_cell __asm__("r8");
    register void **bank_cell __asm__("r4");
    register void **backing_cell __asm__("r5");
    register void *backing __asm__("r6");
    register u32 record_bytes __asm__("r4");
    __asm__("" : "+r"(phase_cell));
    ReleaseBattleRouteRecord((*phase_cell)->route);
    *phase_cell = (struct BattlePhaseContext *)0;
    /* The native caller provides thirteen words without an added capacity guard. */
    actor_count = (s32)CollectBattleUnitRecordAddresses(
        GetContentConsumerContext(), actor_addresses);
    if (actor_count > 0) {
        register u32 *cursor __asm__("r5") = actor_addresses;
        s32 remaining;
        __asm__("" : "+r"(cursor) : "r"(actor_count));
        remaining = actor_count;
        __asm__("" : "+r"(remaining));
        do {
            DisposeBattleContentActor((void *)*cursor++);
            remaining--;
        } while (remaining != 0);
    }
    /* Disposal may change publication; obtain the registry again. */
    ClearFirstWord(ReleaseBattleActionRegistry(GetContentConsumerContext()));
    ClearFirstWord(GetManagedWorkAllocator());
    clear_cell = (MemoryClear *)0x0836d4b8;
    __asm__("" : "+r"(clear_cell));
    bank_cell = (void **)0x0200f4ac;
    __asm__("" : "+r"(bank_cell));
    {
        register void *bank __asm__("r0") = *bank_cell;
        register u32 bank_bytes __asm__("r1");
        register MemoryClear *callback_source __asm__("r3");
        register MemoryClear clear_bytes __asm__("r2");
        __asm__("" : "+r"(bank));
        bank_bytes = 17408;
        __asm__("" : "+r"(bank_bytes) : "r"(bank));
        callback_source = clear_cell;
        __asm__("" : "+r"(callback_source) : "r"(bank), "r"(bank_bytes));
        clear_bytes = *callback_source;
        clear_bytes(bank, bank_bytes);
    }
    ReleaseGlobalPoolAllocation(*bank_cell);
    backing_cell = (void **)0x0200f4b8;
    __asm__("" : "+r"(backing_cell));
    backing = *backing_cell;
    __asm__("" : "+r"(backing));
    record_bytes = ComputeBattleRecordPoolBytes(52);
    __asm__("" : "+r"(record_bytes));
    {
        register u32 backing_bytes __asm__("r1") = BattleObjectIndexOffset(1);
        register MemoryClear *callback_source __asm__("r3");
        register MemoryClear clear_bytes __asm__("r2");
        /* Keep the actual offset return before adding the separate record span. */
        __asm__("" : "+r"(backing_bytes));
        backing_bytes += record_bytes;
        backing_bytes += 0x1668;
        backing_bytes &= ~31u;
        /* This teardown adds32; its constructor's different extent is retained. */
        backing_bytes += 32;
        __asm__("" : "+r"(backing_bytes));
        callback_source = clear_cell;
        __asm__("" : "+r"(callback_source) : "r"(backing_bytes));
        clear_bytes = *callback_source;
        __asm__("" : "+r"(clear_bytes) : "r"(backing_bytes));
        clear_bytes(backing, backing_bytes);
    }
    ReleaseGlobalPoolAllocation(*backing_cell);
    ReleasePublishedBattleIndicator();
    {
        register void **registry_cell __asm__("r1") = (void **)0x0200f4b0;
        register u32 cleared __asm__("r0");
        __asm__("" : "+r"(registry_cell));
        cleared = 0;
        __asm__("" : "+r"(cleared));
        *registry_cell = (void *)cleared;
    }
}
