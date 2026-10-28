typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ClearStateBytes)(void *, u32);
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

/* The caller owns the configuration guard; retain this complete reset order. */
void ResetBattleActivationWorkRegion(void) __asm__("CoreConsumer_000C7260");
void ResetBattleActivationWorkRegion(void)
{
    u8 *region = (u8 *)0x02015738;
    (*(ClearStateBytes *)0x0836d4b8)(region, 248);
    *(u16 *)(region + 176) = 1;
}
