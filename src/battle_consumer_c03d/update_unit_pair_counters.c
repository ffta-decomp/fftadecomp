/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
struct Unit {u8 unknown00[40];u16 flags40;u8 unknown42[172];u16 field214;u8 unknown216[24];u8 value240;u8 unknown241[17];u8 counter258;u8 counter259;u8 key260;};
struct WorkRam {u8 unknown00[0x3c34];u8 pairs[0][2];};
#define OFF(T,M) ((u32)&((T*)0)->M)
typedef char AssertUnitOffsets[(OFF(struct Unit,field214)==214 && OFF(struct Unit,value240)==240 && OFF(struct Unit,counter258)==258 && OFF(struct Unit,counter259)==259 && OFF(struct Unit,key260)==260)?1:-1];
typedef char AssertPairs[(OFF(struct WorkRam,pairs)==0x3c34)?1:-1];
extern struct WorkRam WorkRamBase;
__asm__(".global WorkRamBase\n.set WorkRamBase, 0x02000000");
extern s32 UnitField27HasBit6(const void *unit);
extern s32 UnitField27HasBit14(const void *unit);
extern u8 ReadSaveByte(u16 index);
extern void UpdatePairRecord(u8 key, u8 value, u8 enabled);
__asm__(".global UpdatePairRecord\n.thumb_set UpdatePairRecord, 0x0802dc61");
extern u16 DeriveUnitCounterValue(const void *unit);
__asm__(".global DeriveUnitCounterValue\n.thumb_set DeriveUnitCounterValue, 0x080d2f0d");

__asm__(".global UnitField27HasBit6\n.thumb_set UnitField27HasBit6, 0x080c832d");
__asm__(".global UnitField27HasBit14\n.thumb_set UnitField27HasBit14, 0x080c82b9");

/* Preserve repeated status reads and the two distinct counter/flag continuations. */
u32 UpdateUnitPairCounters(struct Unit *unit, u32 unused1, u32 unused2,
    u32 unused3, u32 unused4, u32 unused5, u8 mode, u32 unused7, u8 selector)
{
    s32 index;
    if (selector == 0)
        return 0;
    index = selector - 1;
    if ((u8)UnitField27HasBit6(unit) != 0 && mode != 3)
        mode = 2;
    if (mode == 1 || (u8)UnitField27HasBit14(unit) == 0)
        UpdatePairRecord(unit->key260, WorkRamBase.pairs[index][0], mode != 1);
    unit->field214 = 0;
    if ((u8)UnitField27HasBit14(unit) != 0)
        mode = 1;
    if (mode != 1) {
        if (unit->counter258 <= 8 && (u8)ReadSaveByte(13) != 1)
            unit->counter258++;
        unit->flags40 |= 104;
        unit->value240 = DeriveUnitCounterValue(unit);
    } else {
        if (unit->counter259 <= 8 && (u8)ReadSaveByte(13) != 1)
            unit->counter259++;
        unit->flags40 |= 64;
    }
    return mode;
}
