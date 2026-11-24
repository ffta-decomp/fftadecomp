typedef unsigned short u16;
struct CoordinateState { unsigned char unknown[36]; u16 x; u16 y; };
void ReadCurrentCoordinates(u16 *out_x,u16 *out_y) __asm__("BattleDependency_0001E6F0");
void ReadCurrentCoordinates(u16 *out_x,u16 *out_y)
{
    struct CoordinateState *state = (struct CoordinateState *)0x02007f40;
    *out_x = state->x;
    *out_y = state->y;
}
