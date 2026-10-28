typedef unsigned char u8;
typedef unsigned int u32;
/* Ordinary live bytes, kept at full width until the later packing operation. */
struct BattleRawPathPositionView { u8 prefix[0x54b4]; u8 x, y; };
typedef char RawXOffset[(u32)&((struct BattleRawPathPositionView *)0)->x == 0x54b4 ? 1 : -1];
typedef char RawYOffset[(u32)&((struct BattleRawPathPositionView *)0)->y == 0x54b5 ? 1 : -1];
extern struct BattleRawPathPositionView gBattleRawPathPositionView;
__asm__(".global gBattleRawPathPositionView\n.set gBattleRawPathPositionView,0x020101f8");
void ReadBattleRawPathPosition(u8 *x_out, u8 *y_out)
{
    *x_out = gBattleRawPathPositionView.x;
    *y_out = gBattleRawPathPositionView.y;
}
