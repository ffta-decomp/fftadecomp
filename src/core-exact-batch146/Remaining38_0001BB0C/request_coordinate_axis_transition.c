#include "../../../src/task_tree_core.h"
typedef signed short s16;
struct CoordinateCurve {
    int from_x,from_y,to_x,to_y,sign_x,sign_y;
    u32 delta_x,delta_y;
    int error,half_delta_y;
    u32 full_delta_y;
};
struct CoordinateTransitionPrefix {
    u8 unknown0[36];
    s16 current_x;
    s16 current_y;
    u8 unknown40[12];
    u8 active;
    u8 phase;
    u16 target_x;
    u16 target_y;
    struct CoordinateCurve curves[2];
};
typedef char CurveSize[sizeof(struct CoordinateCurve)==44?1:-1];
typedef char StatePrefixSize[sizeof(struct CoordinateTransitionPrefix)==148?1:-1];
extern struct CoordinateTransitionPrefix CoordinateTransition;
extern void InitializeCoordinateCurve(struct CoordinateCurve *,int,int,int,int);
u32 RequestCoordinateAxisTransition(u16 target_x,u16 target_y,u16 duration)
{
    if ((s16)target_x == CoordinateTransition.current_x &&
        (s16)target_y == CoordinateTransition.current_y)
        return 0;
    {
        u32 reset_phase = 0;
        int end_frame;
        CoordinateTransition.target_x = target_x;
        CoordinateTransition.target_y = target_y;
        InitializeCoordinateCurve(&CoordinateTransition.curves[0],
            CoordinateTransition.current_x,0,(s16)target_x,
            end_frame = (int)duration - 1);
        InitializeCoordinateCurve(&CoordinateTransition.curves[1],
            CoordinateTransition.current_y,0,(s16)target_y,end_frame);
        CoordinateTransition.active = 1;
        CoordinateTransition.phase = reset_phase;
    }
    return duration;
}
asm(".global CoordinateTransition\n.set CoordinateTransition,0x02007f40\n"
    ".global InitializeCoordinateCurve\n.thumb_set InitializeCoordinateCurve,0x080075cd\n");
