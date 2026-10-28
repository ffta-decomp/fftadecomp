typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Raw field width is retained; interpretation belongs to its consumers. */
struct ReadBattleRawEquipmentView { u8 prefix[0x54c0]; u16 value; };
typedef char ValueOffset[(u32)&((struct ReadBattleRawEquipmentView *)0)->value == 0x54c0 ? 1 : -1];
extern struct ReadBattleRawEquipmentView gReadBattleRawEquipmentView;
__asm__(".global gReadBattleRawEquipmentView\n.set gReadBattleRawEquipmentView,0x020101f8");
u32 ReadBattleRawEquipment(void)
{
    return gReadBattleRawEquipmentView.value;
}
