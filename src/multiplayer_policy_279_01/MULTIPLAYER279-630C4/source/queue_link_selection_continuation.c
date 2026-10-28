typedef unsigned char u8;
typedef unsigned short u16;
union LinkSelectionState {
    struct { u16 selector, depth, continuations[1]; } flow;
    struct { u8 fields_before_pending[77]; u8 pending; } command;
};
extern union LinkSelectionState *gLinkSelectionState;
__asm__(".global gLinkSelectionState\n.set gLinkSelectionState,0x0200f450");

/* The continuation array denotes its observed prefix, not a capacity claim. */
void QueueLinkSelectionContinuation(void)
{
    union LinkSelectionState *state;
    gLinkSelectionState->command.pending = 2;
    state = gLinkSelectionState;
    state->flow.selector = 20;
    state->flow.continuations[state->flow.depth++] = 20;
    state->flow.selector = 49;
}
