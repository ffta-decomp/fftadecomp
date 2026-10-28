typedef unsigned char u8;
typedef unsigned short u16;
struct State { u16 stage,count,queue[0]; };
extern struct State *gState __asm__("0x0200f450");
void RemainingCore48_000644A0(void) {
 register struct State **cell __asm__("r1") = &gState;
 register struct State *first __asm__("r0");
 struct State *state;
 u8 *timer;
 __asm__("" : "+r"(cell));
 first = *cell;
 __asm__("" : "+r"(first));
 timer = (u8 *)first + 81;
 if (*timer != 0) --*timer;
 state = *cell;
 if (((u8 *)state)[81] == 0) state->stage = state->queue[--state->count];
}
