#include "contract.h"
u32 ProcessSceneActorHeightTransition(TaskNode *unused_task,
    struct SceneCoordinateTemplate *event, struct SceneCoordinateState *state)
{
    s32 start_height, end_height, distance;
    u16 duration;
    void *unit;
    switch (event->phase) {
    case 0:
        state->owner = event->owner;
        unit = ResolveSceneUnit((u8)event->unit_selector);
        state->actor = FindPrimaryActor(GetBattleActionRegistry(), unit);
        state->delta_x = event->delta_x;
        state->mode = event->mode;
        state->duration = event->duration;
        break;
    case 0x100:
        start_height = state->actor->height;
        end_height = start_height + state->delta_x;
        if (state->mode == 0) {
            distance = end_height - start_height;
            if (start_height > end_height) distance = start_height - end_height;
            duration = DivideSignedWord((u16)SquareRootWord((u32)distance * distance),state->duration);
        } else {
            duration = state->duration;
        }
        InitializeSceneStep(&state->x_step,start_height,0,(s16)end_height,(s16)duration);
        event->phase = 0x101;
        break;
    case 0x101:
        AdvanceSceneStep(&state->x_step);
        state->actor->height = state->x_step.current;
        if (IsSceneStepComplete(&state->x_step) != 0) {
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
