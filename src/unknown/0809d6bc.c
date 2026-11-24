typedef unsigned char u8;
typedef signed char s8;
struct DirectionStep { s8 x; s8 y; };
extern int SignedDivide(int numerator, int denominator);
asm(".global SignedDivide\n.thumb_set SignedDivide,0x081426b9");
static inline void WriteDirectionStep(s8 direction, s8 *x, s8 *y)
{
    switch (direction) {
    case 0: *x = 0; *y = 1; break;
    case 1: *x = -1; *y = 0; break;
    case 2: *x = 0; *y = -1; break;
    case 3: *x = 1; *y = 0; break;
    default: *x = 0; *y = 0; break;
    }
}
int ChooseBattleDisplacementDirection(u8 delta_x, u8 delta_y)
    asm("CoreConsumer_0009D6BC");
int ChooseBattleDisplacementDirection(u8 delta_x, u8 delta_y)
{
    int signed_x;
    int signed_y;
    int magnitude_x;
    int magnitude_y;
    int index;
    s8 step_x;
    s8 step_y;
    signed_x = (s8)delta_x;
    magnitude_x = __builtin_abs(signed_x);
    signed_y = (s8)delta_y;
    magnitude_y = __builtin_abs(signed_y);
    if (magnitude_x >= magnitude_y) {
        if (signed_x != 0)
            delta_x = SignedDivide(signed_x, __builtin_abs(signed_x));
        delta_y = 0;
    } else {
        if (signed_y != 0)
            delta_y = SignedDivide(signed_y, __builtin_abs(signed_y));
        delta_x = 0;
    }
    for (index = 0; index <= 3; ++index) {
        WriteDirectionStep((s8)index, &step_x, &step_y);
        if (step_x == (s8)delta_x && step_y == (s8)delta_y)
            return index;
    }
    return -1;
}
