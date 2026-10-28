#include "contract.h"
/* Terminal result-message policy; parent handles subsequent scene dispatch. */
u32 SceneRegisteredRoot_0005F2A8(void)
{
    ResultContext *entry_context = gResultContext;
    u8 has_result;
    u32 message;
    switch (entry_context->state) {
    case 0:
        has_result = HasMissionResult();
        message = 82;
        if (has_result != 0)
            message = 83;
        entry_context->message = message;
        ResetDialogStatus();
        StartResultMessage(gResultContext->message);
        gResultContext->state = 1;
        break;
    case 1:
        if ((u16)PollDialogCompletion() != 0) {
            CloseDisplay(0, 0, 0, 0);
            gResultContext->selected_scene = 167;
            gResultContext->state = 255;
            return 1;
        }
        break;
    }
    return 0;
}
