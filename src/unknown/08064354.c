/* Original slot49: create from current byte77, publish menu68 on the
 * post-helper context, then resume its halfword continuation. The same
 * menu68 is consumed by the proven clan mission/trade choice at62248.
 */
typedef unsigned char u8;
typedef unsigned short u16;
struct ChoiceState { u16 state, count, continuation[0]; };
extern struct ChoiceState *gChoiceContext;
extern void *CreateChoiceMenu(unsigned int mode);
asm(".global gChoiceContext\n.set gChoiceContext,0x0200f450\n"
    ".global CreateChoiceMenu\n.thumb_set CreateChoiceMenu,0x08064fa1\n");
void RemainingCore48_00064354(void)
{
    void *menu;
    struct ChoiceState *state;
    menu = CreateChoiceMenu(((u8 *)gChoiceContext)[77]);
    state = gChoiceContext;
    *(void **)((u8 *)state + 68) = menu;
    state->state = state->continuation[--state->count];
}
