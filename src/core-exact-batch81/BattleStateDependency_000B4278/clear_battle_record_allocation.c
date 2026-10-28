typedef unsigned char u8;
struct BattleRecordAllocation { u8 unaccessed[0x1550]; void *allocation; };
extern void ReleaseRecordAllocation(void *);
void ClearBattleRecordAllocation(struct BattleRecordAllocation *record)
{
    void **allocation_slot = &record->allocation;
    ReleaseRecordAllocation(*allocation_slot);
    *allocation_slot = 0;
}
asm(".global ReleaseRecordAllocation\n.thumb_set ReleaseRecordAllocation,0x08022855\n");
