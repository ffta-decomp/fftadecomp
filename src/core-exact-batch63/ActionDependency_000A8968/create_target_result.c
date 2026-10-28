typedef unsigned char u8;
typedef unsigned int u32;

struct BattleTargetResultRecord {
    void *target_context;
    u8 unknown_04[76];
};
typedef char BattleTargetResultMustBe80Bytes[
    sizeof(struct BattleTargetResultRecord) == 80 ? 1 : -1];
typedef void (*ClearBattleRecordBytes)(void *destination, u32 byte_count);
extern void *AllocateBattleRecordBytes(u32 byte_count);
extern ClearBattleRecordBytes const gBattleRecordClearFunction;

struct BattleTargetResultRecord *CreateBattleTargetResultRecord(void *target_context)
{
    struct BattleTargetResultRecord *result = AllocateBattleRecordBytes(80);
    ClearBattleRecordBytes clear_bytes = gBattleRecordClearFunction;
    clear_bytes(result, 80);
    result->target_context = target_context;
    return result;
}

asm(".global AllocateBattleRecordBytes\n.thumb_set AllocateBattleRecordBytes,0x08022841\n"
    ".global gBattleRecordClearFunction\n.set gBattleRecordClearFunction,0x0836d4b8\n");
