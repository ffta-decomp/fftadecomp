typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
struct CoordinateState {
    unsigned char unknown_0000[32];
    u16 projection_x, projection_y;
};
extern struct CoordinateState gCoordinateState;
asm(".global gCoordinateState\n.set gCoordinateState,0x02007f40");

void ProjectBattlePoint(s16 x, s16 height, s16 y,
                       u16 *out_x, u16 *out_y, u16 *out_depth)
{
    s32 horizontal = ((s32)x - y) >> 1;
    s32 combined;
    s32 vertical;
    /* Keep both writes: the output may alias the global projection offsets. */
    *out_x = horizontal;
    horizontal += gCoordinateState.projection_x;
    *out_x = horizontal;
    combined = (s32)x + y;
    vertical = (combined >> 2) - (height >> 1);
    *out_y = vertical;
    vertical += gCoordinateState.projection_y;
    *out_y = vertical;
    *out_depth = combined;
}
