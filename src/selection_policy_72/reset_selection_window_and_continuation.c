/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[32];void *window;u8 gap[12];u32 flags;int choice,result,previous_choice;u16 signature_a,signature_b;};
extern struct Selection *gSelection;
extern void ResetSelectionWindow(void *);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global ResetSelectionWindow\n.thumb_set ResetSelectionWindow,0x8066029");
void ResetSelectionWindowAndContinuation(void)
{
    struct Selection *selection = gSelection;
    selection->signature_a = 0x9004;
    selection->signature_b = 0x1237;
    selection->previous_choice = 0;
    ResetSelectionWindow(selection->window);
    {
        struct Selection *next = gSelection;
        next->state = 48;
        next->stack[next->depth++] = 48;
        next->state = 57;
        next->stack[next->depth++] = 57;
        next->state = 50;
        next->flags &= ~64u;
    }
}
