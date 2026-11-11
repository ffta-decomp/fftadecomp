typedef unsigned char u8;
typedef unsigned int u32;
struct MissionItemRecord { u8 occupied; u8 unknown[3]; };
extern struct MissionItemRecord gMissionItemBank[];
__asm__(".global gMissionItemBank\n.set gMissionItemBank,0x02002b08");
u32 CollectMissionRequiredItems(struct MissionItemRecord **output)
{
    struct MissionItemRecord *record=gMissionItemBank;
    u32 count=0;
    int remaining=63;
    u32 cursor=(u32)output;
    do {
        if (record->occupied != 0) {
            if (output != 0) *(struct MissionItemRecord **)cursor=record;
            cursor+=4;
            count++;
        }
        --remaining;
        record++;
    } while (remaining>=0);
    return count;
}
