typedef unsigned char u8;
typedef unsigned int u32;
struct BattleUnitListContext;
struct BattleRecordWorkset {
    const struct BattleUnitListContext *context;
    u32 *record_addresses;
    u8 unknown_08[9];
    u8 count;
    u8 unknown_18[74];
};
typedef char WorksetSize[sizeof(struct BattleRecordWorkset)==92?1:-1];
typedef char CountOffset[(u32)&(((struct BattleRecordWorkset *)0)->count)==17?1:-1];
typedef void (*ClearBytesFunction)(void *, u32);
extern void *AllocateGlobalPoolBytes(u32);
extern u32 CollectBattleUnitRecordAddresses(const struct BattleUnitListContext *, u32 *);
struct BattleRecordWorkset *CreateBattleRecordWorkset(const struct BattleUnitListContext *context)
{
    struct BattleRecordWorkset *workset;
    u32 *records;
    workset = AllocateGlobalPoolBytes(92);
    (*(ClearBytesFunction *)0x0836d4b8)(workset, 92);
    workset->context = context;
    records = AllocateGlobalPoolBytes(52);
    workset->record_addresses = records;
    workset->count = CollectBattleUnitRecordAddresses(context, records);
    return workset;
}
asm(".global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes,0x08022841\n"
    ".global CollectBattleUnitRecordAddresses\n.thumb_set CollectBattleUnitRecordAddresses,0x08099cdd\n");
asm(".global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n");
asm(".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n");
asm(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");
asm(".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");
asm(".global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n");
asm(".global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n");
asm(".global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n");
