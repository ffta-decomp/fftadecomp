typedef unsigned char u8;
typedef unsigned int u32;
struct BattlePhaseFlagView { u8 unknown_00[208]; u32 flags; };
u32 AdvanceBattlePhasePollFlags(void) __asm__("ClearContentGlobalFlag800AndSet1000");
u32 AdvanceBattlePhasePollFlags(void)
{
    struct BattlePhaseFlagView *phase = *(struct BattlePhaseFlagView **)0x0200f4a8;
    u32 flags = (phase->flags & ~0x800u) | 0x1000u;
    phase->flags = flags;
    /* Keep the native R0 result; direct callers have not been established. */
    return flags;
}
