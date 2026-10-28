/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 ReadSaveByte(u16 index);
extern u8 ReadGameFlag(u32 index);
extern u8 UnitField27HasBit15(const void *unit);
extern u8 UnitField27HasBit14(const void *unit);
extern u8 TargetMode_0012F3CC(const void *unit);
extern u8 ActorPredicate_00133BC4(const void *unit);

asm(".global ReadGameFlag\n.thumb_set ReadGameFlag,0x080c9541\n.global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9\n.global TargetMode_0012F3CC\n.thumb_set TargetMode_0012F3CC,0x0812f3cd\n.global ActorPredicate_00133BC4\n.thumb_set ActorPredicate_00133BC4,0x08133bc5");
static inline u8 HasSaveAndUnitStatus(const void *unit)
{
    if (!ReadSaveByte(13) || !UnitField27HasBit15(unit) || !UnitField27HasBit14(unit))
        return 0;
    return 1;
}
u32 ActorTargetPassesStatusPolicy(const void *actor, const void *target)
{
    if (TargetMode_0012F3CC(target) == 1)
        goto success;
    if (!HasSaveAndUnitStatus(target) || !ReadGameFlag(65) || UnitField27HasBit15(actor))
        goto failure;
    if (ReadGameFlag(66)) {
        if (ActorPredicate_00133BC4(actor))
            goto failure;
        goto success;
    } else {
        if (ActorPredicate_00133BC4(actor))
            goto success;
    }
failure:
    return 0;
success:
    return 1;
}
