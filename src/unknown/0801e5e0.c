typedef unsigned short u16;
typedef signed short s16;
struct CoordinateState { unsigned char unknown[36]; u16 x; s16 y; };
extern void RefreshCoordinateState(void);
extern void RefreshChangedVerticalCoordinate(void);
__asm__(".global RefreshCoordinateState\n.thumb_set RefreshCoordinateState,0x08019e85\n.global RefreshChangedVerticalCoordinate\n.thumb_set RefreshChangedVerticalCoordinate,0x0801da11");
void SetCurrentCoordinates(int x,s16 y) __asm__("BattleDependency_0001E5E0");
void SetCurrentCoordinates(int x,s16 y)
{
    unsigned int changed = 0;
    struct CoordinateState *state = (struct CoordinateState *)0x02007f40;
    state->x = x;
    {
    register int current_y __asm__("r0") = state->y;
    /* Native materializes the signed current Y before comparing incoming Y. */
    __asm__("" : "+r"(current_y));
    if (current_y != y) {
        state->y = y;
        changed = 1;
    }
    }
    RefreshCoordinateState();
    if (changed)
        RefreshChangedVerticalCoordinate();
}
