#include "../../../src/task_tree_core.h"
typedef signed short s16;
typedef signed int s32;
struct RelativeCoordinateState {
    u8 unknown_00[36];
    u16 x;
    u16 y;
};
extern struct RelativeCoordinateState gRelativeCoordinateState;
void GetRelativeBattleCoordinates(s32 x, s32 y, u16 *out_x, u16 *out_y)
{
    u16 current_x = gRelativeCoordinateState.x;
    register s32 signed_x asm("r0") = (s16)x;
    /* The native signed working value is consumed after its current-X sample. */
    asm("" : "+r" (signed_x));
    *out_x = signed_x - current_x;
    {
        u16 current_y = gRelativeCoordinateState.y;
        register s32 signed_y asm("r1") = (s16)y;
        /* Preserve the second narrowing after the alias-visible first store. */
        asm("" : "+r" (signed_y));
        *out_y = signed_y - current_y;
    }
}
asm(".global gRelativeCoordinateState\n.set gRelativeCoordinateState,0x02007f40\n");
