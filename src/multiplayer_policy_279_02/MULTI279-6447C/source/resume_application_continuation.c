typedef unsigned short u16;
struct State { u16 stage; u16 count; u16 queue[0]; };
extern struct State *gState __asm__("0x0200f450");
extern void CloseCurrent(void) __asm__("RetailCall_08013364");
void RemainingCore48_0006447C(void) {
 struct State *state;
 CloseCurrent();
 state = gState;
 state->stage = state->queue[--state->count];
}
__asm__(".global RetailCall_08013364\n.thumb_set RetailCall_08013364,0x08013365");
