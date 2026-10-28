typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RecordContinuationHeader { u16 state, depth; };
struct BattleRouteRecord {
    u8 unaccessed_prefix[220];
    struct RecordContinuationHeader continuation;
    u8 unaccessed_tail[68];
};
typedef char BattleRouteRecordSize[(sizeof(struct BattleRouteRecord) == 292) ? 1 : -1];
typedef void (*ClearBattleRecord)(void *destination, u32 bytes);
extern void *AllocateBattleRecord(u32 bytes);
extern ClearBattleRecord const gBattleRecordClear;
struct BattleRouteRecord *CreateBattleRouteRecord(void)
{
    struct BattleRouteRecord *record = AllocateBattleRecord(sizeof(struct BattleRouteRecord));
    ClearBattleRecord clear = gBattleRecordClear;
    clear(record, sizeof(struct BattleRouteRecord));
    {
        struct RecordContinuationHeader *continuation = &record->continuation;
        continuation->depth = 0;
    }
    return record;
}
asm(".global AllocateBattleRecord\n.thumb_set AllocateBattleRecord,0x08022841\n"
    ".global gBattleRecordClear\n.set gBattleRecordClear,0x0836D4B8\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224D\n");
