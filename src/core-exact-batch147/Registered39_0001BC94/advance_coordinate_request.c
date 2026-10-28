#include "../../../src/task_tree_core.h"
typedef signed short s16;
union CoordinateValue {
    int word;
    struct { s16 low; u16 high; } halves;
};
struct CoordinateCurve {
    union CoordinateValue from_x;
    int from_y,to_x,to_y,sign_x,sign_y;
    u32 delta_x,delta_y;
    int error,half_delta_y;
    u32 full_delta_y;
};
struct CoordinateStatePrefix {
    u8 unknown0[36];
    s16 current_x,current_y;
    u8 unknown40[12];
    u8 active,phase;
    u16 target_x,target_y;
    struct CoordinateCurve curves[2];
};
typedef char CurveSize[sizeof(struct CoordinateCurve)==44?1:-1];
typedef char StateSize[sizeof(struct CoordinateStatePrefix)==148?1:-1];
extern struct CoordinateStatePrefix CoordinateState;
extern void AdvanceCoordinateCurve(struct CoordinateCurve *);
extern u32 IsCoordinateCurveComplete(const struct CoordinateCurve *);
extern void AdvanceAdaptiveCoordinateRequest(void);
extern void SetCurrentCoordinates(int,s16);
void AdvanceCoordinateRequest(void)
{
    if (CoordinateState.active) {
        if (CoordinateState.phase == 1) {
            AdvanceAdaptiveCoordinateRequest();
        } else {
            struct CoordinateCurve *curve_x = &CoordinateState.curves[0];
            struct CoordinateCurve *curve_y;
            AdvanceCoordinateCurve(curve_x);
            curve_y = &CoordinateState.curves[1];
            AdvanceCoordinateCurve(curve_y);
            /* Native uses the genuine low-half X view, but reads Y as a word. */
            SetCurrentCoordinates(curve_x->from_x.halves.low,
                                  (s16)curve_y->from_x.word);
            if (IsCoordinateCurveComplete(curve_x)) {
                if (IsCoordinateCurveComplete(curve_y))
                    CoordinateState.active = 0;
            }
        }
    }
}
asm(".global CoordinateState\n.set CoordinateState,0x02007f40\n"
    ".global AdvanceCoordinateCurve\n.thumb_set AdvanceCoordinateCurve,0x080076a1\n"
    ".global IsCoordinateCurveComplete\n.thumb_set IsCoordinateCurveComplete,0x08007881\n"
    ".global AdvanceAdaptiveCoordinateRequest\n.thumb_set AdvanceAdaptiveCoordinateRequest,0x0801b899\n"
    ".global SetCurrentCoordinates\n.thumb_set SetCurrentCoordinates,0x0801e5e1\n");
