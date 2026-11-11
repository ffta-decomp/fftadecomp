typedef unsigned char u8;
typedef unsigned int u32;
struct BattleContext;
typedef void (*MemoryClear)(void *, u32);
extern u32 ComputeBattleRecordPoolBytes(u32);
extern u32 BattleObjectIndexOffset(u8);
extern void *AllocateBattleBacking(u32);
extern void *InitializePublishedBattleHeap(void *, u32);
extern struct BattleContext *CreatePublishedBattleContext(void *);
__asm__(".global ComputeBattleRecordPoolBytes\n.thumb_set ComputeBattleRecordPoolBytes,0x08022081\n.global BattleObjectIndexOffset\n.thumb_set BattleObjectIndexOffset,0x0814913d\n.global AllocateBattleBacking\n.thumb_set AllocateBattleBacking,0x08022841\n.global InitializePublishedBattleHeap\n.thumb_set InitializePublishedBattleHeap,0x080070c9\n.global CreatePublishedBattleContext\n.thumb_set CreatePublishedBattleContext,0x08097001\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
void InitializeBattleRuntimeStorage(void)
{
    u32 record_bytes = ComputeBattleRecordPoolBytes(52);
    u32 byte_count = BattleObjectIndexOffset(1);
    void **backing_slot;
    void *backing;
    void *pool;
    struct BattleContext *context;
    byte_count += record_bytes;
    byte_count += 0x1668;
    byte_count &= ~31U;
    backing_slot = (void **)0x0200f4b8;
    byte_count += 1056;
    backing = AllocateBattleBacking(byte_count);
    *backing_slot = backing;
    (*(const MemoryClear *)0x0836d4b8)(backing, byte_count);
    pool = InitializePublishedBattleHeap(*backing_slot, byte_count);
    *(void **)0x0200f4b4 = pool;
    context = CreatePublishedBattleContext(pool);
    *(struct BattleContext **)0x0200f4b0 = context;
}
