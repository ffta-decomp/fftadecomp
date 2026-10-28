typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Raw field width is retained; interpretation belongs to its consumers. */
struct ReadBattleRawActionView { u8 prefix[0x54be]; u16 value; };
typedef char ValueOffset[(u32)&((struct ReadBattleRawActionView *)0)->value == 0x54be ? 1 : -1];
extern struct ReadBattleRawActionView gReadBattleRawActionView;
__asm__(".global gReadBattleRawActionView\n.set gReadBattleRawActionView,0x020101f8");
u32 ReadBattleRawAction(void)
{
    return gReadBattleRawActionView.value;
}
