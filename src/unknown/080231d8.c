typedef unsigned char u8;
extern void ResetInputCallbackState(void);
extern u8 PollMenuInputState(void);
void PollMenuInputCallback(void)
{
 ResetInputCallbackState();
 PollMenuInputState();
}
__asm__(".global Registered39_000231D8\n.thumb_set Registered39_000231D8,PollMenuInputCallback\n.global ResetInputCallbackState\n.thumb_set ResetInputCallbackState,0x0808f789\n.global PollMenuInputState\n.thumb_set PollMenuInputState,0x08022c65\n");
