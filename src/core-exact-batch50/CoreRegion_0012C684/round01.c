typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
/* Difference wrap and signed magnitude reinterpretation are original byte rules. */
u32 IsBattleDirectionWedgeAccepted(s8 first_x, s8 first_y, s8 second_x,
    s8 second_y, u8 direction_x, u8 direction_y) asm("CoreRegion_0012C684");
u32 IsBattleDirectionWedgeAccepted(s8 first_x, s8 first_y, s8 second_x,
    s8 second_y, u8 direction_x, u8 direction_y)
{
    s8 delta_x;
    u8 delta_y;
    u8 absolute_x, absolute_y;
    int signed_direction_x;
    delta_x = first_x - second_x;
    delta_y = first_y - second_y;
    absolute_x = (u8)__builtin_abs(delta_x);
    absolute_y = (u8)__builtin_abs((s8)delta_y);
    signed_direction_x = (s8)direction_x;
    if (delta_x * signed_direction_x < 0)
        return 0;
    if ((s8)delta_y * (s8)direction_y < 0)
        return 0;
    if (signed_direction_x != 0) {
        if ((s8)absolute_y > (s8)absolute_x)
            return 0;
    } else {
        if ((s8)absolute_x > (s8)absolute_y)
            return 0;
    }
    return 1;
}
