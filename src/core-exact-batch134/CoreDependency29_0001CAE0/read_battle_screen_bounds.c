#include "../../../src/task_tree_core.h"
struct BattleScreenGridBounds {
    u8 unknown_00[46];
    u8 minimum_x;
    u8 minimum_y;
    u8 maximum_x;
    u8 maximum_y;
};
extern struct BattleScreenGridBounds gBattleScreenGridBounds;

void ReadBattleScreenBounds(u16 *output)
{
    u32 left = gBattleScreenGridBounds.minimum_x << 3;
    u32 top;
    u32 right;
    u32 bottom;
    output[0] = left;
    top = gBattleScreenGridBounds.minimum_y << 3;
    output[1] = top;
    right = (gBattleScreenGridBounds.maximum_x << 3) + 8;
    output[2] = right;
    bottom = (gBattleScreenGridBounds.maximum_y << 3) + 8;
    output[3] = bottom;
    output[4] = right - left;
    output[5] = bottom - top;
}
asm(".global gBattleScreenGridBounds\n.set gBattleScreenGridBounds,0x02007f40\n");
