typedef unsigned short u16;
struct ExchangeApplication { u16 stage, depth; u16 continuations[116]; void (*callback)(unsigned); };
extern struct ExchangeApplication *gExchangeApplication;
extern void UpdateExchangeApplication(unsigned);
asm(".global gExchangeApplication\n.set gExchangeApplication,0x0200f450\n.global UpdateExchangeApplication\n.thumb_set UpdateExchangeApplication,0x08061f55");
void RestoreExchangeApplicationContinuation(void)
{
    struct ExchangeApplication *state;
    UpdateExchangeApplication(0);
    state = gExchangeApplication;
    state->callback = UpdateExchangeApplication;
    state->stage = state->continuations[--state->depth];
}
