typedef unsigned char u8;
typedef unsigned int u32;
/* Ordinary live bytes, kept at full width until the later packing operation. */
struct BattleRawPositionView { u8 prefix[0x54b2]; u8 x, y; };
typedef char RawXOffset[(u32)&((struct BattleRawPositionView *)0)->x == 0x54b2 ? 1 : -1];
typedef char RawYOffset[(u32)&((struct BattleRawPositionView *)0)->y == 0x54b3 ? 1 : -1];
extern struct BattleRawPositionView gBattleRawPositionView;
__asm__(".global gBattleRawPositionView\n.set gBattleRawPositionView,0x020101f8");
void ReadBattleRawPosition(u8 *x_out, u8 *y_out)
{
    *x_out = gBattleRawPositionView.x;
    *y_out = gBattleRawPositionView.y;
}
