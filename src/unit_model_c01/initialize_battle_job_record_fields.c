typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ReadBattleJobPair(u8 index, u16 *first, u16 *second);
asm(".global ReadBattleJobPair\n.thumb_set ReadBattleJobPair, 0x0812f195");
extern u32 GetJobProperty(u8 job, u8 fallback, u8 property);

void InitializeBattleJobRecordFields(u8 *record, u8 index)
{
    u16 first;
    u16 second;

    ReadBattleJobPair(index, &first, &second);
    record[104] = GetJobProperty((u8)first, (u8)first, 13);
    record[104] = GetJobProperty((u8)first, (u8)first, 13);
    record[105] = 1;
    record[106] = GetJobProperty((u8)first, (u8)first, 14);
    record[107] = GetJobProperty((u8)first, (u8)first, 15);
    record[108] = GetJobProperty((u8)first, (u8)first, 16);
    record[109] = GetJobProperty((u8)first, (u8)first, 17);
    record[110] = GetJobProperty((u8)first, (u8)first, 18);
    record[111] = GetJobProperty((u8)first, (u8)first, 19);
    record[112] = GetJobProperty((u8)first, (u8)first, 20);
    record[113] = GetJobProperty((u8)first, (u8)first, 21);
}
