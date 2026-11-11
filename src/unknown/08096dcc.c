typedef unsigned char u8;
typedef unsigned int u32;
struct BattlePhaseFlagView { u8 unknown_00[208]; u32 flags; };
u32 ClearBattlePhaseFlags8800(void) __asm__("ClearContentGlobalFlags8800");
u32 ClearBattlePhaseFlags8800(void)
{
    struct BattlePhaseFlagView *phase = *(struct BattlePhaseFlagView **)0x0200f4a8;
    u32 flags = phase->flags & ~0x8800u;
    phase->flags = flags;
    /* Native R0 is preserved; bit0x8000 intent and entry callers remain unknown. */
    return flags;
}
