typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ClearStateBytes)(void *, u32);
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

/* These offsets and defaults are observed; their wider interpretation is unknown. */
void ResetBattleWorkRegionMode(void) __asm__("CoreFrontier_000C7284");
void ResetBattleWorkRegionMode(void)
{
    u8 *region = (u8 *)0x02015738;
    (*(ClearStateBytes *)0x0836d4b8)(region, 248);
    *(u16 *)(region + 176) = 1;
    region[172] = 7;
}
