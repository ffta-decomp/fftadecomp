typedef unsigned char u8;
typedef unsigned int u32;
struct BattlePhaseFlagView { u8 unknown_00[208]; u32 flags; };
void UpdateBattlePhaseFlag2000(u8 clear_flag) __asm__("UpdateContentGlobalFlag2000");
void UpdateBattlePhaseFlag2000(u8 clear_flag)
{
    struct BattlePhaseFlagView *phase = *(struct BattlePhaseFlagView **)0x0200f4a8;
    if (clear_flag != 0)
        phase->flags &= ~0x2000u;
    else
        phase->flags |= 0x2000u;
}
