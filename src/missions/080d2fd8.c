/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
struct ProgressRecord {u8 unknown;u8 flags;u8 value;u8 tail[9];};
extern struct ProgressRecord gProgress[];
extern void SetIndexedFlag(int,int);
extern void SetGameFlag(int,int);

asm(".global gProgress\n.set gProgress,0x02002cb4\n.global SetIndexedFlag\n.thumb_set SetIndexedFlag,0x80c95c1\n.global SetGameFlag\n.thumb_set SetGameFlag,0x80c9575");
void ResetMissionProgressEntry(u8 index)
{
    unsigned int record_offset = index * 12;
    struct ProgressRecord *record = (void *)((u8 *)gProgress + record_offset);
    record->flags &= 245;
    record->value = 0;
    SetIndexedFlag(index+20,0);
    SetGameFlag(0x59f,0);
    SetGameFlag(index+0x580,1);
}
