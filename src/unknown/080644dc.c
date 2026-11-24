typedef unsigned char u8;
typedef unsigned short u16;
struct State { u16 stage,count,queue[0]; };
extern struct State *gState __asm__("0x0200f450");
extern void RequestPolicy(u16) __asm__("RetailCall_080c71b4");
void RemainingCore48_000644DC(void) {
 struct State *state;
 RequestPolicy(((u8 *)gState)[80]);
 state = gState;
 state->stage = state->queue[--state->count];
}
__asm__(".global RetailCall_080c71b4\n.thumb_set RetailCall_080c71b4,0x080c71b5");
