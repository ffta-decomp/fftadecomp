typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ExchangeState {
    u16 stage, depth;
    u16 continuations[38];
    u8 unknown80, delay, error, unknown83;
    u32 flags;
    u8 unknown88[12];
    u16 code, expected, acknowledgments[2];
};
struct LinkStatus {
    u8 flags, unknown1, type, unknown3[285];
    u16 interrupt, elapsed;
    u8 pacing;
};
struct LinkMessage { u16 unknown0, code, payload; };
extern struct ExchangeState *gExchangeState;
extern struct LinkStatus gLinkStatus;
extern struct LinkMessage gLinkReceive, gLinkTransmit;
asm(".global gExchangeState\n.set gExchangeState,0x0200f450\n.global gLinkStatus\n.set gLinkStatus,0x030028a0\n.global gLinkReceive\n.set gLinkReceive,0x03002890\n.global gLinkTransmit\n.set gLinkTransmit,0x03002b50");
void BeginExchangeConfirmation(void)
{
    struct ExchangeState *state = gExchangeState;
    if (!(state->flags & 16)) {
        state->flags &= ~32u;
        state->stage = state->continuations[--state->depth];
        return;
    }
    state->acknowledgments[1] = 0;
    state->acknowledgments[0] = 0;
    gLinkTransmit.payload = 0;
    gLinkTransmit.code = 0;
    gLinkReceive.payload = 0;
    gLinkReceive.code = 0;
    if (gLinkStatus.pacing != 1) {
        if (gLinkStatus.interrupt != 0 || (gLinkStatus.elapsed > 200 && gLinkStatus.type != 3)) {
            if (state->flags & 32) {
                state->flags &= ~32u;
                state->error = 255;
                {
                    struct ExchangeState *resumed = gExchangeState;
                    resumed->stage = resumed->continuations[--resumed->depth];
                }
                return;
            }
            state->stage = 68;
            state->continuations[state->depth++] = 68;
            state->stage = 52;
            state->continuations[state->depth++] = 52;
            state->stage = 54;
        }
        return;
    }
    state->acknowledgments[(gLinkStatus.flags & 8) == 0] = state->expected;
    state->delay = 16;
    gExchangeState->stage = 58;
}
