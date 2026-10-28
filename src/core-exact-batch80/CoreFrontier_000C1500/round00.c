typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Raw field width is retained; interpretation belongs to its consumers. */
struct ReadBattleRawUnitAttributeView { u8 prefix[0x54ba]; u8 value; };
typedef char ValueOffset[(u32)&((struct ReadBattleRawUnitAttributeView *)0)->value == 0x54ba ? 1 : -1];
extern struct ReadBattleRawUnitAttributeView gReadBattleRawUnitAttributeView;
__asm__(".global gReadBattleRawUnitAttributeView\n.set gReadBattleRawUnitAttributeView,0x020101f8");
u32 ReadBattleRawUnitAttribute(void)
{
    return gReadBattleRawUnitAttributeView.value;
}
