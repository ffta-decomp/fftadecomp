#include "../../../src/task_tree_core.h"
typedef signed short s16;
union CoordinateValue { int word; struct { s16 low; u16 high; } halves; };
struct CoordinateCurve {
    union CoordinateValue from_x;
    int from_y,to_x,to_y,sign_x,sign_y;
    u32 delta_x,delta_y;
    int error,half_delta_y;
    u32 remaining_steps;
};
struct CoordinateRequest {
    u8 active,phase;
    s16 target_x,target_y;
    struct CoordinateCurve curves[2];
    u8 minimum_control,second_control,control_delta,current_control;
    u32 half_distance;
    u8 decelerating;
};
struct CoordinateStatePrefix { u8 unknown0[36]; s16 current_x,current_y; };
typedef char CurveSize[sizeof(struct CoordinateCurve)==44?1:-1];
typedef char RequestSize[sizeof(struct CoordinateRequest)==108?1:-1];
extern struct CoordinateRequest CoordinateRequest;
extern struct CoordinateStatePrefix CoordinateState;
extern void AdvanceCoordinateCurveBy(struct CoordinateCurve *,u16);
extern void SetCurrentCoordinates(int,s16);
void AdvanceAdaptiveCoordinateRequest(void)
{
    struct CoordinateRequest *request = &CoordinateRequest;
    /* Keep the real request header as the address anchor; no hard binding. */
    asm("" : "+r" (request));
    AdvanceCoordinateCurveBy(&request->curves[0],
                             request->current_control);
    AdvanceCoordinateCurveBy(&request->curves[1],
                             request->current_control);
    SetCurrentCoordinates(request->curves[0].from_x.halves.low,
                          request->curves[1].from_x.halves.low);
    if (request->decelerating == 0) {
        if (request->curves[0].remaining_steps <= request->half_distance)
            request->decelerating = 1;
        if (request->decelerating == 0) {
            request->current_control += request->control_delta;
            goto check_completion;
        }
    }
    /* The subtraction wraps as a byte before the observed minimum comparison. */
    request->current_control -= request->control_delta;
    if (request->current_control < request->minimum_control)
        request->current_control = request->minimum_control;
check_completion:
    if (request->target_x == CoordinateState.current_x &&
        request->target_y == CoordinateState.current_y)
        request->active = 0;
}
asm(".global CoordinateRequest\n.set CoordinateRequest,0x02007f74\n"
    ".global CoordinateState\n.set CoordinateState,0x02007f40\n"
    ".global AdvanceCoordinateCurveBy\n.thumb_set AdvanceCoordinateCurveBy,0x0800777d\n"
    ".global SetCurrentCoordinates\n.thumb_set SetCurrentCoordinates,0x0801e5e1\n");
