#include "interfaces.h"
u8 CoreFrontier_0005E354(void)
{
    u8 *state_byte;
    u32 state_value;
    switch (ReadPanelOutcome()) {
    case 1:
    case 2:
        if (gGameContext.count==4) {
            gGameContext.cursor=0;
            gGameContext.count=3;
        }
        ClosePanel(5,1);
        SetSlotDisplay(0);
        {
            struct MissionContext **root_cell = &gMissionContext;
            /* Actual cell survives the conditional write, then supplies a fresh root. */
            __asm__("" : "+r"(root_cell));
            if ((*root_cell)->unit) (*root_cell)->continuation=20;
            else (*root_cell)->continuation=12;
            state_byte=&(*root_cell)->state;
            goto state_one;
        }
        goto accepted;
    case 3:
    case 4: {
        register u32 shifted_index __asm__("r0") = (u32)ReadPanelIndex() << 16;
        u32 index;
        s32 signed_index;
        /* One actual shifted return word feeds both original extraction sites. */
        __asm__("" : "+r"(shifted_index));
        index = shifted_index >> 16;
        signed_index = (s32)shifted_index >> 16;
        if (signed_index<0) {
            switch (gMissionContext->stage) {
            default:
                ClosePanel(5,0);
                gMissionContext->stage=0;
                gMissionContext->continuation=10;
                state_byte=&gMissionContext->state;
                goto state_one;
            case 0:
                CloseMessage();
                ShowMessage(80);
                gMissionContext->stage=1;
                gMissionContext->continuation=10;
                state_byte=&gMissionContext->state;
                state_value=3;
                goto store_state;
            case 1:
                if (gKeys.pressed&3) {
                    CloseMessage();
                    ShowMessage((u8)ResolveProgressChoiceCode(0));
                    gMissionContext->stage=2;
                    gMissionContext->continuation=10;
                    state_byte=&gMissionContext->state;
                    state_value=3;
                    goto store_state;
                }
                break;
            }
            goto accepted;
        }
        if (signed_index<=1) {
            gMissionContext->slot=index;
            SetParticipantSlot(gMissionContext->slot);
            CloseMessage();
            gMissionContext->continuation=11;
            state_byte=&gMissionContext->state;
            state_value=3;
        } else {
            gGameContext.cursor=3;
            gGameContext.count=4;
            ClosePanel(5,1);
            gMissionContext->continuation=12;
            state_byte=&gMissionContext->state;
            state_value=1;
        }
        /* Both original nonnegative edges meet before the one store/call tail. */
        *state_byte=state_value;
        SetSlotDisplay(0);
        goto accepted;
    }
    case 6: {
        s16 index=ReadPanelIndex();
        if (index<=1) {
            ClearParticipantSlot((u16)index);
            PopulatePanel(gMissionContext->records,gMissionContext->candidate_count+2);
            SelectPanelRow(5,index);
            if (index!=2) {
                struct Participant *participant=gMissionContext->records[gMissionContext->candidate_count+index];
                if (!participant) SetSlotDisplay(0);
            }
            gMissionContext->continuation=10;
            state_byte=&gMissionContext->state;
            goto state_one;
        }
        goto accepted;
    }
    case 5:
    default:
        goto rejected;
    }
state_one:
    state_value=1;
store_state:
    *state_byte=state_value;
accepted:
    return 1;
rejected:
    return 0;
}
