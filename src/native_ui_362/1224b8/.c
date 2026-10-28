#include "interfaces.h"
u32 UpdateSceneContextModeFromCommand(struct SceneContext *context,const u8 *command)
{
    context->mode=command[1];
    switch(context->mode) {
    case 3: context->mode=1;InitializeSceneModeThree();break;
    case 6: context->mode=3;break;
    case 7: context->mode=5;break;
    case 9:
        {
            register const struct ModeState *state asm("r0") = SceneModeState;
            asm("" : "+r"(state));
            if(state->mode==3 || GetGameFlag(64)) return 272;
        }
        PrepareSceneModeNine();
        if(!IsSceneModeNineReady()) return 272;
        RunSceneModeNine(context);
        return 277;
    case 10:RunSceneModeTen(context);return 277;
    case 11:RunSceneModeEleven(context);return 277;
    case 14:RunSceneModeFourteen(context);return 277;
    }
    return 284;
}
