typedef unsigned char u8;
struct RecordGroup;
struct BattleOwnedRecord { u8 unaccessed[0x1554]; struct RecordGroup *group; void *membership; };
extern void RemoveBattleRecordMembership(struct RecordGroup *, void *);
extern void DestroyBattleRecordGroup(struct RecordGroup *);
extern void ReleaseBattleRecordAllocation(void *);
void ReleaseBattleOwnedRecord(struct BattleOwnedRecord *record)
{
    if (record != 0) {
        struct RecordGroup **group_slot = &record->group;
        RemoveBattleRecordMembership(*group_slot, record->membership);
        DestroyBattleRecordGroup(*group_slot);
        ReleaseBattleRecordAllocation(record);
    }
}
asm(".global RemoveBattleRecordMembership\n.thumb_set RemoveBattleRecordMembership,0x08021bd5\n.global DestroyBattleRecordGroup\n.thumb_set DestroyBattleRecordGroup,0x08021b55\n.global ReleaseBattleRecordAllocation\n.thumb_set ReleaseBattleRecordAllocation,0x08022855\n");
