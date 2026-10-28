typedef unsigned char u8;
struct BattleRecord {
    u8 unknown_000[60];
    u8 *transient_object;
};
extern void ClearBattleObjectTransientState(u8 *object);
__asm__(".global ClearBattleObjectTransientState\n.thumb_set ClearBattleObjectTransientState, 0x081492a9");

/* Reuse the existing object's clear operation with the observed full pointer. */
void ClearBattleRecordTransientState(struct BattleRecord *record)
    __asm__("CoreFrontier_00099F00");
void ClearBattleRecordTransientState(struct BattleRecord *record)
{
    ClearBattleObjectTransientState(record->transient_object);
}
