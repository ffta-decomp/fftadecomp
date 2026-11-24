typedef unsigned char u8;
typedef unsigned short u16;
struct ApplicationExchangeState {
    u16 stage;
    u8 unknown2[90];
    u8 payload[4];
    u8 unknown96[12];
    u8 sequence[96];
};
extern struct ApplicationExchangeState *gExchangeState __asm__("0x0200f450");
extern void RequestPolicyMode(u16) __asm__("RetailCall_080c71b4");
extern void InitializeTransfer(void *,void *,u16,u8) __asm__("RetailCall_080c73c4");

void RemainingCore48_0006417C(void)
{
    struct ApplicationExchangeState **cell;
    struct ApplicationExchangeState *state;
    RequestPolicyMode(1);
    cell = &gExchangeState;
    state = *cell;
    InitializeTransfer(state->sequence,state->payload,4,2);
    (*cell)->stage = 45;
}
__asm__(".global RetailCall_080c71b4\n.thumb_set RetailCall_080c71b4,0x080c71b5\n"
        ".global RetailCall_080c73c4\n.thumb_set RetailCall_080c73c4,0x080c73c5");
