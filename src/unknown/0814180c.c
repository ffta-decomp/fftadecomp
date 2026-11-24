typedef unsigned char u8;
typedef unsigned short u16;
struct SequenceContext { unsigned int field_0; u16 state_4; };
extern u8 gContextGate;
extern struct SequenceContext gFixedContext;
__asm__(".set gContextGate,0x020084d8\n.set gFixedContext,0x0200f2a0");
unsigned int IsEnabledContextActive(void) __asm__("CoreDependency29_0014180C");
unsigned int IsEnabledContextActive(void)
{
    unsigned int state;
    if (gContextGate & 1)
        goto enabled;
    return 0;
enabled:
    state = gFixedContext.state_4;
    if (state != 0)
        state = 1;
    return state;
}
