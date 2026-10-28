#include "contract.h"
/* Coordinates and mode describe observed accesses; producer domains remain unknown. */
u32 ProcessSceneActorCoordinateTransition(TaskNode *unused_task,
    struct SceneCoordinateTemplate *event, struct SceneCoordinateState *state)
{
    s32 start_x, start_y, end_x, end_y;
    s32 distance_x, distance_y;
    u32 squared_distance;
    u16 duration;
    s16 step_duration;
    u32 first_complete;
    u32 second_complete;
    void *unit;
    switch (event->phase) {
    case 0:
        state->owner = event->owner;
        unit = ResolveSceneUnit((u8)event->unit_selector);
        state->actor = FindPrimaryActor(GetBattleActionRegistry(), unit);
        state->delta_x = event->delta_x;
        state->delta_y = event->delta_y;
        state->mode = event->mode;
        state->duration = event->duration;
        break;
    case 0x100:
        start_x = state->actor->x;
        end_x = start_x + state->delta_x;
        start_y = state->actor->y;
        end_y = start_y + state->delta_y;
        if (state->mode == 0) {
            distance_x = end_x - start_x;
            if (start_x > end_x) distance_x = start_x - end_x;
            distance_y = end_y - start_y;
            if (start_y > end_y) distance_y = start_y - end_y;
            squared_distance = (u32)distance_x * distance_x;
            squared_distance += (u32)distance_y * distance_y;
            duration = DivideSignedWord((u16)SquareRootWord(squared_distance), state->duration);
        } else {
            duration = state->duration;
        }
        step_duration = (s16)duration;
        InitializeSceneStep(&state->x_step,start_x,0,(s16)end_x,step_duration);
        InitializeSceneStep(&state->y_step,start_y,0,(s16)end_y,step_duration);
        event->phase = 0x101;
        break;
    case 0x101:
        AdvanceSceneStep(&state->x_step);
        AdvanceSceneStep(&state->y_step);
        state->actor->x = state->x_step.current;
        state->actor->y = state->y_step.current;
        first_complete = IsSceneStepComplete(&state->x_step);
        second_complete = IsSceneStepComplete(&state->y_step);
        if (first_complete != 0 && second_complete != 0) {
            state->owner->complete = 1;
            event->phase = 3;
        }
        break;
    case 0x103:
        state->owner->complete = 1;
        event->phase = 3;
        break;
    }
    return 0;
}
asm(".global ResolveSceneUnit\n.thumb_set ResolveSceneUnit,0x08125579\n"
    ".global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n"
    ".global FindPrimaryActor\n.thumb_set FindPrimaryActor,0x08099561\n"
    ".global SquareRootWord\n.thumb_set SquareRootWord,0x08141899\n"
    ".global DivideSignedWord\n.thumb_set DivideSignedWord,0x081426b9\n"
    ".global InitializeSceneStep\n.thumb_set InitializeSceneStep,0x08007621\n"
    ".global AdvanceSceneStep\n.thumb_set AdvanceSceneStep,0x080076f5\n"
    ".global IsSceneStepComplete\n.thumb_set IsSceneStepComplete,0x08007895\n");
