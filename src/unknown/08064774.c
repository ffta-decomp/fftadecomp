typedef unsigned short u16;
struct ExchangeResultState {
    u16 stage, depth;
    u16 continuations[48];
    u16 result_code, result_detail;
};
extern struct ExchangeResultState *gExchangeResultState;
asm(".global gExchangeResultState\n.set gExchangeResultState,0x0200f450");
void PublishExchangeResultAndResume(void)
{
    struct ExchangeResultState *state = gExchangeResultState;
    state->result_code = 0x9002;
    state->result_detail = 0x1235;
    state->stage = state->continuations[--state->depth];
}
