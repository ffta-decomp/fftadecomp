typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ClearStateBytes)(void *, u32);
struct WorkSubregion {
    u8 unknown_000[2];
    u8 field_002;
    u8 unknown_003;
    u16 field_004;
    u16 field_006;
};
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

/* Field meanings are unresolved; preserve the original widths and write order. */
void InitializeBattleWorkSubregion(void) __asm__("CoreConsumer_000C7214");
void InitializeBattleWorkSubregion(void)
{
    struct WorkSubregion *region = (struct WorkSubregion *)0x02015744;
    (*(ClearStateBytes *)0x0836d4b8)(region, 144);
    region->field_002 = 0;
    region->field_004 = 216;
    region->field_006 = 152;
}
