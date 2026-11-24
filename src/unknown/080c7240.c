typedef unsigned int u32;
typedef void (*ClearStateBytes)(void *, u32);
extern void InitializeBattleWorkSubregion(void);
__asm__(".global InitializeBattleWorkSubregion\n.thumb_set InitializeBattleWorkSubregion, 0x080c7215\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

/* The nested initializer's overlapping clear and default writes remain real. */
void InitializeBattleWorkRegion(void) __asm__("CoreConsumer_000C7240");
void InitializeBattleWorkRegion(void)
{
    void *region = (void *)0x02015738;
    /* Form the native destination literal before the callback address load.
     * This defined read/write operand emits no instruction or memory effect. */
    __asm__("" : "+r"(region));
    (*(ClearStateBytes *)0x0836d4b8)(region, 248);
    InitializeBattleWorkSubregion();
}
