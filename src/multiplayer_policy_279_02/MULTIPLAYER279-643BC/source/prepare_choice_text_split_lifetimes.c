/* Slot51 consumes the same message byte78 selected by the proven62248
 * clan mission/trade decision. Preserve both post-helper context reloads.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ChoiceState { u16 state, count, continuation[0]; };
extern struct ChoiceState *gChoiceContext;
extern void PrepareChoiceText(void *, unsigned int);
extern void ApplyChoiceTextFlag(unsigned int);
asm(".global gChoiceContext\n.set gChoiceContext,0x0200f450\n"
    ".global PrepareChoiceText\n.thumb_set PrepareChoiceText,0x08061029\n"
    ".global ApplyChoiceTextFlag\n.thumb_set ApplyChoiceTextFlag,0x080133b1\n");
void RemainingCore48_000643BC(void)
{
    struct ChoiceState *state;
    {
        u8 *choice = (u8 *)gChoiceContext;
        void *text = choice + 240;
        unsigned int message = choice[78];
        PrepareChoiceText(text, message);
    }
    if (*(u32 *)((u8 *)gChoiceContext + 84) & 4)
        ApplyChoiceTextFlag(4096);
    state = gChoiceContext;
    state->state = state->continuation[--state->count];
}
