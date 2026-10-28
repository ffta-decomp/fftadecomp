/* Method-local interface declarations from the frozen build. */
#ifndef FLAG_FLOW_INTERFACES_H
#define FLAG_FLOW_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct FlagFlowContext {
    u16 selector;
    u16 depth;
    u16 saved_selectors[36];
    u8 field76;
    u8 pending;
    u16 transition;
    u32 field80;
    u32 flags;
} FlagFlowContext;
typedef char flags_offset_check[((unsigned long)&((FlagFlowContext *)0)->flags == 84) ? 1 : -1];
extern u8 GetGameFlag(u16 flag);
extern void SetGameFlag(u16 flag, u16 value);
extern FlagFlowContext * volatile gFlagFlowContext;
__asm__(".global gFlagFlowContext\n.set gFlagFlowContext, 0x0200f450");
#define FLOW_ROOT gFlagFlowContext
#endif


void ScheduleFlag63FlowContinuation(void)
{
    FlagFlowContext *initial = FLOW_ROOT;
    FlagFlowContext *flag_context;
    FlagFlowContext *continuing;
    FlagFlowContext *scheduled;
    u16 depth;
    u32 flags;
    u32 continuation;

    if (initial->flags & 8)
        initial->transition = 166;
    else if ((u8)GetGameFlag(63) == 0) {
        FLOW_ROOT->transition = 164;
        SetGameFlag(63, 1);
    } else
        FLOW_ROOT->transition = 165;

    flag_context = FLOW_ROOT;
    flags = flag_context->flags | 16;
    continuation = 2;
    flag_context->flags = flags | continuation;
    flag_context->pending = 1;
    scheduled = FLOW_ROOT;
    if (scheduled->transition == 166) {
        scheduled->selector = continuation;
        depth = scheduled->depth++;
        scheduled->saved_selectors[depth] = continuation;
        scheduled->selector = 49;
    } else
        scheduled->selector = 3;

    continuing = FLOW_ROOT;
    depth = continuing->depth++;
    continuing->saved_selectors[depth] = continuing->selector;
    continuing->selector = 52;
    depth = continuing->depth++;
    continuing->saved_selectors[depth] = 52;
    continuing->selector = 51;
}
