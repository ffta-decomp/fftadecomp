/* Method-local interface declarations from the frozen build. */
#ifndef CHOICE_FLOW_INTERFACES_H
#define CHOICE_FLOW_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef struct ChoiceFlowContext {
    u16 selector;
    u16 depth;
    u16 saved_selectors[36];
    u8 field76;
    u8 pending;
    u16 transition;
    u32 field80;
    u32 flags;
    volatile s32 choice;
    u8 fields92[16];
    u8 input[126];
    s16 previous_choice;
    u8 fields236[1948];
    void *associated_record;
} ChoiceFlowContext;
typedef char choice_offset_check[((unsigned long)&((ChoiceFlowContext *)0)->choice == 88) ? 1 : -1];
typedef char previous_offset_check[((unsigned long)&((ChoiceFlowContext *)0)->previous_choice == 234) ? 1 : -1];
typedef char record_offset_check[((unsigned long)&((ChoiceFlowContext *)0)->associated_record == 2184) ? 1 : -1];
extern ChoiceFlowContext * volatile gChoiceFlowContext;
extern void * volatile gContentState;
__asm__(".global gChoiceFlowContext\n.set gChoiceFlowContext, 0x0200f450");
extern u8 PollChoiceFlowInput(void *input);
extern void RequestFlowMode(u16 mode);
extern void *SelectFlowContentRecord(void);
__asm__(".global PollChoiceFlowInput\n.thumb_set PollChoiceFlowInput, 0x080c73d9\n.global RequestFlowMode\n.thumb_set RequestFlowMode, 0x080c71b5\n.global SelectFlowContentRecord\n.thumb_set SelectFlowContentRecord, 0x08061c9d");
extern u8 GetGameFlag(u16 flag);
extern void SetGameFlag(u16 flag, u16 value);
#endif


void AdvanceChoiceFlowContinuation(void)
{
    u8 result = PollChoiceFlowInput(gChoiceFlowContext->input);
    ChoiceFlowContext *pending;
    ChoiceFlowContext *comparing;
    ChoiceFlowContext *committing;
    u16 depth;
    void *record;

    if (result != 0) {
        if (result == 2) {
            pending = gChoiceFlowContext;
            pending->selector = 68;
            depth = pending->depth++;
            pending->saved_selectors[depth] = 68;
            pending->selector = 52;
            depth = pending->depth++;
            pending->saved_selectors[depth] = 52;
            pending->selector = 54;
        }
        return;
    }

    RequestFlowMode(3);
    if (GetGameFlag(579) != 0)
        SetGameFlag(58, 1);

    comparing = gChoiceFlowContext;
    if (comparing->previous_choice != comparing->choice) {
        comparing->transition = 172;
        switch (comparing->choice) {
        case 1: comparing->transition = 172; break;
        case 2: comparing->transition = 184; break;
        case 3: comparing->transition = 192; break;
        }
        gChoiceFlowContext->selector = 47;
    } else {
        record = SelectFlowContentRecord();
        gContentState = record;
        committing = gChoiceFlowContext;
        committing->associated_record = record;
        committing->selector = 7;
    }
}
