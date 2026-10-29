#include "interfaces.h"
/* Mission-specific confirmation, cancellation and option-wrap policy. */
void AdvanceMissionInteractionChoice(u8 mode) __asm__("CoreFrontier_0005DAA8");
void AdvanceMissionInteractionChoice(u8 mode)
{
    int changed=0;
    u16 pressed=gKeys.pressed;
    u8 first_count;
    struct GameContext *options;
    gMissionContext->transient=1;
    first_count = gGameContext.count;
    options = &gGameContext;
    /* Separate the initial count read from the real navigation-cache definition. */
    __asm__("" : : "r" (options));
    if (first_count==4) {
        if (mode==0) {
            if (pressed&1) {
                gMissionContext->transient=0;
                ShowChoiceDialogue(gMissionContext->dialog,2);
                gMissionContext->continuation=13;
                gMissionContext->state=2;
                return;
            } else if (pressed&2) {
                PlayChoiceSoundGroup(1,105);
                CloseMessage();
                gMissionContext->transient=0;
                gMissionContext->message=ResolveProgressChoiceCode(1);
                gMissionContext->second_continuation=9;
                gMissionContext->continuation=18;
                gMissionContext->state=2;
                return;
            }
        } else if (pressed&1) {
            register u8 *state_target __asm__("r0");
            u32 state_value;
            if (MissionHasRuleBit4(gMissionContext->mission)) {
                ShowChoiceDialogue(gMissionContext->dialog,3);
                gMissionContext->continuation=13;
                state_target = &gMissionContext->state;
                __asm__("" : "+r" (state_target));
            } else {
                PlayChoiceSound(100);
                CloseMessage();
                gMissionContext->continuation = 0;
                state_target = &gMissionContext->state;
                __asm__("" : "+r" (state_target));
            }
            /* Original state2 is defined at this shared store, after both addresses. */
            state_value = 2;
            __asm__("" : "+r" (state_value));
            *state_target = state_value;
            gMissionContext->transient=0;
            return;
        }
    }
    if (pressed&2) {
        PlayChoiceSoundGroup(1,105);
        gMissionContext->selection_flag=0;
        gMissionContext->control=1;
        CloseMessage();
        gMissionContext->transient=0;
        gMissionContext->continuation=0;
        gMissionContext->state=2;
    } else if (pressed&1) {
        PlayChoiceSound(100);
        CloseMessage();
        gMissionContext->transient=0;
        gMissionContext->continuation=6;
        gMissionContext->state=2;
    } else if (pressed&16) {
        changed=1;
        if (options->cursor<options->count-1) ++options->cursor;
        else options->cursor=0;
    } else if (pressed&32) {
        int cursor;
        changed=1;
        cursor=options->cursor;
        if (cursor==0) cursor=options->count;
        options->cursor=cursor-1;
    }
    if (changed) {
        PlayChoiceSound(109);
        CloseMessage();
        SetMessageChoice(9,gGameContext.cursor);
        gMissionContext->continuation=5;
        gMissionContext->state=2;
    }
}
