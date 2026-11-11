#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed int s32;
struct BattleActor { void *unit; };
struct ViewContinuation { u16 selector, depth, values[1]; };
struct CoordinateActorView {
    struct BattleActor *actor;
    u8 previous_x, previous_y;
    u16 unknown_06;
    void *view;
    struct ViewContinuation continuation;
};
extern struct BattleActor *FindActorAtPosition(void *context, s32 x, s32 y);
extern void *ObtainActorView(u32 kind);
extern void RequestActorViewTransition(void *view);
extern void *CreateActorUnitView(void *unit, u32 mode);
extern u32 ReadActorViewStatus(void *view);
asm(".global FindActorAtPosition\n.thumb_set FindActorAtPosition,0x0809961d\n"
    ".global ObtainActorView\n.thumb_set ObtainActorView,0x0802d72d\n"
    ".global RequestActorViewTransition\n.thumb_set RequestActorViewTransition,0x0802d705\n"
    ".global CreateActorUnitView\n.thumb_set CreateActorUnitView,0x0802b70d\n"
    ".global ReadActorViewStatus\n.thumb_set ReadActorViewStatus,0x0802b881");

void AdvanceBattleCoordinateActorView(void *,u8,u8) asm("CoreFrontier_00092638");
void AdvanceBattleCoordinateActorView(void *context, u8 x, u8 y)
{
    switch (*(u16 *)0x0200f6ac) {
    case 0: {
        struct CoordinateActorView *state = (void *)0x0200f6a0;
        struct BattleActor *actor;
        if (x == state->previous_x && y == state->previous_y)
            goto update_coordinates;
        actor = FindActorAtPosition(context, (s8)x, (s8)y);
        if (state->actor == actor)
            goto update_coordinates;
        if (actor == 0 && state->actor != 0) {
            if (state->view == 0)
                state->view = ObtainActorView(1);
            RequestActorViewTransition(state->view);
            state->actor = actor;
        } else {
            struct CoordinateActorView *open_state = (void *)0x0200f6a0;
            open_state->actor = actor;
            open_state->view = CreateActorUnitView(actor->unit, 0);
        }
        goto update_coordinates;
    }
    case 1: {
        struct CoordinateActorView *state = (void *)0x0200f6a0;
        if (state->view == 0)
            state->view = ObtainActorView(1);
        RequestActorViewTransition(state->view);
        state->continuation.selector = 2;
        return;
    }
    case 2: {
        struct CoordinateActorView *state = (void *)0x0200f6a0;
        if (((u8)ReadActorViewStatus(ObtainActorView(1)) & ~16u) == 3) {
            register struct ViewContinuation *continuation asm("r2") = (void *)0x0200f6ac;
            register u32 depth asm("r0");
            register u16 *values_base asm("r1");
            register u32 byte_offset asm("r0");
            register u16 *selected_value asm("r0");
            asm("" : "+r"(continuation));
            depth = continuation->depth - 1;
            asm("" : "+r"(depth));
            continuation->depth = depth;
            byte_offset = (u32)(u16)depth << 1;
            asm("" : "+r"(byte_offset));
            values_base = continuation->values;
            asm("" : "+r"(values_base));
            asm volatile("add %0, %0, %1" : "+l" (byte_offset) : "l" (values_base) : "cc");
            selected_value = (u16 *)byte_offset;
            asm("" : "+r"(selected_value));
            continuation->selector = *selected_value;
        }
        return;
    }
    case 3: {
        struct CoordinateActorView *state = (void *)0x0200f6a0;
        state->view = CreateActorUnitView(state->actor->unit, 0);
        state->continuation.selector = 4;
        return;
    }
    case 4: {
        register struct CoordinateActorView *state asm("r4") = (void *)0x0200f6a0;
        asm("" : "+r"(state));
        if (((u8)ReadActorViewStatus(state->view) & ~16u) == 2) {
            register struct ViewContinuation *continuation asm("r1") = &state->continuation;
            register u32 depth asm("r0");
            register u16 *values_base asm("r1");
            asm("" : "+r" (continuation), "+r" (state));
            depth = continuation->depth - 1;
            continuation->depth = depth;
            depth = (u32)(u16)depth << 1;
            asm("" : "+r" (depth));
            values_base = continuation->values;
            asm("" : "+r" (values_base), "+r" (state));
            asm volatile("add %0, %0, %1" : "+l" (depth) : "l" (values_base) : "cc");
            state->continuation.selector = *(u16 *)depth;
        }
        return;
    }
    }
update_coordinates:
    {
        struct CoordinateActorView *state = (void *)0x0200f6a0;
        state->previous_x = x;
        state->previous_y = y;
    }
}
