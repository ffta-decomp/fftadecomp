typedef unsigned char u8;
typedef unsigned short u16;
struct ChoiceState { u16 state, count, stack[0]; };
extern struct ChoiceState *gChoiceContext;
extern void PrepareChoiceMessage(void);
extern void ShowChoiceMessage(unsigned int);
__asm__(".global gChoiceContext\n.set gChoiceContext,0x0200f450\n.global PrepareChoiceMessage\n.thumb_set PrepareChoiceMessage,0x08013365\n.global ShowChoiceMessage\n.thumb_set ShowChoiceMessage,0x080610f9");
void ShowMultiplayerChoiceMessage(void)
{
    struct ChoiceState *state;
    PrepareChoiceMessage();
    ShowChoiceMessage(((u8 *)gChoiceContext)[78]);
    state=gChoiceContext;
    state->state=state->stack[--state->count];
}
