/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit { u8 unknown00[24]; u16 field19; };
typedef char AssertField19[((u32)&((struct Unit *)0)->field19==24)?1:-1];
extern u8 TestE86(const void *unit);
__asm__(".global TestE86\n.thumb_set TestE86, 0x80cd92d");
extern u8 TestE97(const void *unit);
__asm__(".global TestE97\n.thumb_set TestE97, 0x80cda05");
extern u8 TestEA7(const void *unit);
__asm__(".global TestEA7\n.thumb_set TestEA7, 0x80cdadd");
extern u8 TestEB2(const void *unit);
__asm__(".global TestEB2\n.thumb_set TestEB2, 0x80cdb25");
extern u8 TestEC1(const void *unit);
__asm__(".global TestEC1\n.thumb_set TestEC1, 0x80cda4d");

/* Retain both E9 bit7 calls: the original has two distinct read sites. */
u32 UnitPassesEffectStateGates(const struct Unit *unit)
{
    if (unit->field19 == 0 ||
        (u8)TestE86(unit) != 0 ||
        (u8)TestE97(unit) != 0 ||
        (u8)TestE97(unit) != 0 ||
        (u8)TestEA7(unit) != 0 ||
        (u8)TestEB2(unit) != 0 ||
        (u8)TestEC1(unit) != 0)
        goto reject;
    return 1;
reject:
    return 0;
}
