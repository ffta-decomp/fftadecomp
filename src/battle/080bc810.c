/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct UnitRecord { const void *unit; };
extern const u32 gClearMemory;
extern void *GetSceneActionContextBase(void);
extern const struct UnitRecord *GetSelectedUnitRecord(void *context);
extern u8 CheckUnitEligibility(const void *unit);
extern u8 *AllocateScratch(u32 size);
extern void FreeScratch(void *scratch);
extern void CallR2Trampoline(void *destination, u32 size, u32 routine);
extern void PopulateScratch(u8 *scratch, const void *value, u8 first, u8 second);

asm(".global GetSceneActionContextBase\n.thumb_set GetSceneActionContextBase,0x8096d7d\n.global GetSelectedUnitRecord\n.thumb_set GetSelectedUnitRecord,0x8099545\n.global CheckUnitEligibility\n.thumb_set CheckUnitEligibility,0x812e4a9\n.global AllocateScratch\n.thumb_set AllocateScratch,0x8022841\n.global FreeScratch\n.thumb_set FreeScratch,0x8022855\n.global PopulateScratch\n.thumb_set PopulateScratch,0x80bb5c5");
u32 EvaluateSelectedUnitScratchRule(const void *value, u8 first, u8 second)
{
    const struct UnitRecord *record = GetSelectedUnitRecord(GetSceneActionContextBase());
    u8 *scratch;
    u32 result;
    if (!record || !CheckUnitEligibility(record->unit))
        return 0;
    scratch = AllocateScratch(192);
    CallR2Trampoline(scratch, 192, gClearMemory);
    PopulateScratch(scratch, value, first, second);
    result = scratch[110] != 0;
    FreeScratch(scratch);
    return result;
}
