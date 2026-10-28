/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state;u16 depth;u16 stack[32];void *window;u8 gap[9];u8 pending;u8 rejected;};
extern struct Selection *gSelection;
extern void ResetSelectionWindow(void *);
extern void PlaySelectionFeedback(u16);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global ResetSelectionWindow\n.thumb_set ResetSelectionWindow,0x8066029\n.global PlaySelectionFeedback\n.thumb_set PlaySelectionFeedback,0x81416dd");
void AdvanceSelectionWindowResponse(void)
{
    struct Selection *selection;
    u16 previous_depth, previous;
    ResetSelectionWindow(gSelection->window);
    PlaySelectionFeedback(15);
    selection = gSelection;
    if (!selection->rejected) {
        selection->state = 68;
        selection->stack[selection->depth++] = 68;
        selection->state = 52;
        selection->stack[selection->depth++] = 52;
        selection->state = 54;
        selection->stack[selection->depth++] = 54;
        selection->state = 50;
    } else {
        struct Selection *resumed;
        selection->pending = 16;
        resumed = gSelection;
        previous_depth = resumed->depth;
        previous = resumed->stack[--resumed->depth];
        resumed->state = previous;
        resumed->depth = previous_depth;
        resumed->stack[(u16)(previous_depth - 1)] = previous;
        resumed->state = 50;
    }
}
