typedef unsigned int u32;
struct AbilitySelection;
extern struct AbilitySelection *gAbilitySelection;
asm(".global gAbilitySelection\n.set gAbilitySelection,0x0200f438\n");

/* Clear the current game selection root; R0 returns the stored zero. */
u32 CoreGlobal36_000294B0(void)
{
    gAbilitySelection = 0;
    return 0;
}
