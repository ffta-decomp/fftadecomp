typedef unsigned char u8;
typedef unsigned int u32;
struct BattlePhaseFlagView { u8 unknown_00[208]; u32 flags; };
void SetBattlePhaseFlags8800(void) __asm__("AddContentGlobalFlags8800");
void SetBattlePhaseFlags8800(void)
{
    register u32 *flags_address __asm__("r1") =
        &(*(struct BattlePhaseFlagView **)0x0200f4a8)->flags;
    /* Bit0x800 enters the observed phase poll; bit0x8000's role remains partial. */
    __asm__("" : "+r"(flags_address));
    *flags_address |= 0x8800;
}
