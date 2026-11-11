typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitReactionView { u8 unknown00[261]; u8 primary; u8 unknown106; u8 fallback; };
extern u32 RetailCall_0812f0cc(const struct UnitReactionView *,void *);
extern u32 RetailCall_080cd50c(const struct UnitReactionView *);
extern u32 RetailCall_08002804(void);
extern s32 RetailCall_08142950(s32,s32);
asm(".global RetailCall_0812f0cc\n.thumb_set RetailCall_0812f0cc,0x0812f0cd\n.global RetailCall_080cd50c\n.thumb_set RetailCall_080cd50c,0x080cd50d\n.global RetailCall_08002804\n.thumb_set RetailCall_08002804,0x08002805\n.global RetailCall_08142950\n.thumb_set RetailCall_08142950,0x08142951");

u32 CoreConsumer_000C13C8(const struct UnitReactionView *incoming_unit)
{
    register const struct UnitReactionView *unit __asm__("r4")=incoming_unit;
    u32 scratch;
    u32 count;
    u8 unit_class;
    const u8 *primary;
    register const u8 *fallback __asm__("r1");
    /* Read the initialized R4 snapshot without defining a new pointer value. */
    asm("" : : "r"(unit));
    count=(u8)RetailCall_0812f0cc(incoming_unit,&scratch);
    unit_class=RetailCall_080cd50c(unit);
    if ((unit_class==8 && count==2) || count==1)
        return 0;
    primary=&unit->primary;
    if (*primary && (s16)RetailCall_08142950((s16)RetailCall_08002804(),101)<=30)
        return *primary;
    fallback=&unit->fallback;
    /* The independently defined native fallback address is consumed in R1. */
    asm("" : : "r"(fallback));
    if (*fallback)
        return *fallback;
    return 0;
}
