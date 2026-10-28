/* Original application-choice slot61. Keep menu close, post-helper current
 * reload, queue62 publication and transfer to the existing slot50 wait.
 */
typedef unsigned short u16;
struct ChoiceState { u16 state, count, continuation[0]; };
extern struct ChoiceState *gChoiceContext;
extern void CloseChoiceMenu(void *);
asm(".global gChoiceContext\n.set gChoiceContext,0x0200f450\n"
    ".global CloseChoiceMenu\n.thumb_set CloseChoiceMenu,0x08066029\n");
void RemainingCore48_00064870(void)
{
    struct ChoiceState *state;
    CloseChoiceMenu(*(void **)((unsigned char *)gChoiceContext + 68));
    state = gChoiceContext;
    state->state = 62;
    state->continuation[state->count++] = state->state;
    state->state = 50;
}
