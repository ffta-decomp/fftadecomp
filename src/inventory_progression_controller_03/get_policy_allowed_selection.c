/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ContentRecord {void *unit; u8 gap[44]; u32 flags;};
struct MissionState {u8 gap[0x3c32];u8 count;u8 alignment;u16 entries[0];};
struct Selection {u8 gap[6];u8 selected;};
extern struct ContentRecord *GetContentContextPointerAt4(void);
extern void *GetContentConsumerContext(void);
extern u8 GetGameFlag(u32);
extern void *FindContentEntryWithUnitFlag12(void *);
extern u8 UnitField27HasBit15(void *);
extern u8 Predicate8260(void *);
extern int CheckContextUnit(void *,void *);
extern u8 CheckOption(int);

asm(".global Predicate8260\n.thumb_set Predicate8260,0x80c8261\n.global CheckContextUnit\n.thumb_set CheckContextUnit,0x80970e9\n.global CheckOption\n.thumb_set CheckOption,0x80ced5d");
asm(".global GetContentContextPointerAt4\n.thumb_set GetContentContextPointerAt4,0x8096d89\n.global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x8096d7d\n.global FindContentEntryWithUnitFlag12\n.thumb_set FindContentEntryWithUnitFlag12,0x8099545");
extern struct MissionState gMission;
asm(".global gMission\n.set gMission,0x02000000");
u32 GetPolicyAllowedSelection(void)
{
    struct ContentRecord *record = GetContentContextPointerAt4();
    int index;
    int count;
    u16 *entry;
    struct MissionState *mission;
    if (!GetGameFlag(0x207)) goto unavailable;
    index = 0;
    mission = &gMission;
    if (index < mission->count) {
        count = mission->count;
        entry = mission->entries;
        do {
            switch (*entry) {
            case 0: break;
            case 83: goto unavailable;
            }
            entry++;
            index++;
        } while (index < count);
    }
    if (!FindContentEntryWithUnitFlag12(GetContentConsumerContext())) goto unavailable;
    if (UnitField27HasBit15(record->unit)) goto unavailable;
    if (Predicate8260(record->unit)) goto unavailable;
    if (record->flags & 0x8000) goto unavailable;
    if (CheckContextUnit(GetContentConsumerContext(),record->unit)) goto unavailable;
    if (CheckOption(1)) goto unavailable;
    return (*(struct Selection **)0x0200f444)->selected;
unavailable:
    return 0;
}
