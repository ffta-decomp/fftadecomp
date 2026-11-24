typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;

/* Signed query coordinates are compared with stored unsigned byte values. */
u32 ContainsBattlePoint(const u8 *points, s32 count, u8 x, u8 y)
{
    s32 index = 0;
    if (index < count) {
        s32 signed_x = (s8)x;
        s32 signed_y = (s8)y;
        do {
            if (signed_x == points[0] && signed_y == points[1])
                return 1;
            ++index;
            points += 4;
        } while (index < count);
    }
    return 0;
}
