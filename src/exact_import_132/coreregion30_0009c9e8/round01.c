#include "interfaces.h"
int CoreRegion30_0009C9E8(struct MotionRecord *other,struct VisitContext *context)
{
    struct Bounds subject_bounds,other_bounds;
    struct MotionRecord *subject;
    int height_difference;
    if(context->subject==other) return 1;
    if(other->unit->active==0) return 1;
    if(RetailCall_080cdadc(other->unit)) return 1;
    if(RetailCall_080cdb24(other->unit)) return 1;
    if(RetailCall_080cd92c(other->unit)) return 1;
    if(other->flags&4) return 1;
    if(other->pending!=0) context->pending=1;
    height_difference=context->subject->height-other->height;
    if(height_difference<0) height_difference=-height_difference;
    if(RetailCall_0809c8c8(other,1)!=0) return 1;
    if(height_difference>47) return 1;
    subject=context->subject;
    subject_bounds.left=subject->x-16;
    subject_bounds.right=subject->x+16;
    subject_bounds.top=subject->y-16;
    subject_bounds.bottom=subject->y+16;
    other_bounds.left=other->x-16;
    other_bounds.right=other->x+16;
    other_bounds.top=other->y-16;
    other_bounds.bottom=other->y+16;
    if(!(subject_bounds.left<other_bounds.right && subject_bounds.right>other_bounds.left && subject_bounds.top<other_bounds.bottom && subject_bounds.bottom>other_bounds.top)) {
        other->flags=0;
        return 1;
    }
    if(other->flags&2) return 1;
    if(other->motion14!=0) return 1;
    if(other->motion16!=0) return 1;
    context->pending=1;
    RetailCall_0809c6b8(subject->identity,other,1);
    return 1;
}
