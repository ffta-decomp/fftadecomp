typedef unsigned short u16;
typedef unsigned int u32;
extern void *AllocateGlobalPoolBytes(u32 byte_count);
extern void InitializeBattlePhaseRecord(void *record, void *source, u16 value);
asm(".global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes,0x08022841\n.global InitializeBattlePhaseRecord\n.thumb_set InitializeBattlePhaseRecord,0x080bbbb1");

void *CreateBattlePhaseRecord(void *source, u16 value)
{
    void *record = AllocateGlobalPoolBytes(84);
    InitializeBattlePhaseRecord(record, source, value);
    return record;
}
