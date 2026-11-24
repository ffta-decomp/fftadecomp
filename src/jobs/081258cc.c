/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct UnitRecord { u8 prefix[4]; u8 active; u8 rest[259]; };
extern struct UnitRecord gUnitPoolB[];
extern const u32 gClearMemory;
extern u8 UnitPredicate_000C8364(struct UnitRecord *unit);
extern u8 UnitField01Equals(struct UnitRecord *unit, u8 value);
extern void SetGameFlag(u32 index, u8 value);
extern void UnitMutation_000CB4C0(struct UnitRecord *unit);
extern void CallR2Trampoline(void *destination, u32 size, u32 routine);

asm(".global UnitPredicate_000C8364\n.thumb_set UnitPredicate_000C8364,0x080c8365\n.global UnitMutation_000CB4C0\n.thumb_set UnitMutation_000CB4C0,0x080cb4c1");
void ClearFlaggedSceneUnits(void)
{
    struct UnitRecord *unit = gUnitPoolB;
    u32 *flags = (u32 *)((u8 *)unit + 0x3ba4);
    int remaining;
    for (remaining = 23; remaining >= 0; remaining--, unit++) {
        if (unit->active && UnitPredicate_000C8364(unit)) {
            if (UnitField01Equals(unit, 8))
                SetGameFlag(52, 1);
            UnitMutation_000CB4C0(unit);
            CallR2Trampoline(unit, 264, gClearMemory);
            *flags |= 8;
        }
    }
}
