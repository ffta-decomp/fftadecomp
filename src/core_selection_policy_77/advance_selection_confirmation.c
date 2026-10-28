/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[37];u16 message;u8 unknown80,pending;u8 gap[2];u32 flags;int choice,result;u8 gap96[4];u16 signature_a,signature_b;};
struct Current {u32 value;int selected;};
struct Game {u8 gap[0x1f64];u32 currency;u8 gap2[0x20d0-0x1f68];struct Current current;};
extern struct Selection *gSelection;
extern struct Game gGame;
extern u32 PollDialog(void);
extern u32 ReadDialogResult(void);
extern void CloseDialog(void);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global gGame\n.set gGame,0x02000000\n.global PollDialog\n.thumb_set PollDialog,0x8011861\n.global ReadDialogResult\n.thumb_set ReadDialogResult,0x8013381\n.global CloseDialog\n.thumb_set CloseDialog,0x8013365");
void AdvanceSelectionConfirmation(void)
{
    if ((u16)PollDialog()) {
        int result = (s8)ReadDialogResult();
        if (result < 0) {
            struct Selection *selection = gSelection;
            selection->flags = (selection->flags & ~1u) | 4;
            CloseDialog();
            {
                struct Selection *next = gSelection;
                next->state = 31;
                next->stack[next->depth++] = 31;
                next->state = 52;
                next->stack[next->depth++] = 52;
                next->state = 66;
            }
        } else if (result > 0) {
            struct Selection *selection = gSelection;
            selection->flags &= ~1u;
            selection->flags &= ~4u;
            selection->choice = -1;
            selection->result = -1;
            selection->message = 196;
            selection->signature_a = 0x9001;
            selection->signature_b = 0x1234;
            selection->state = 33;
            selection->stack[selection->depth++] = 33;
            selection->state = 55;
            selection->stack[selection->depth++] = 55;
            selection->state = 52;
            selection->stack[selection->depth++] = 52;
            selection->state = 54;
            selection->stack[selection->depth++] = 54;
            selection->state = 43;
            selection->stack[selection->depth++] = 43;
            selection->state = 40;
            selection->stack[selection->depth++] = 40;
            selection->state = 57;
            selection->stack[selection->depth++] = 57;
            selection->state = 52;
            selection->stack[selection->depth++] = 52;
            selection->state = 53;
            selection->stack[selection->depth++] = 53;
            selection->state = 66;
        } else if (gGame.currency <= 4999) {
            struct Selection *selection = gSelection;
            selection->flags &= ~1u;
            selection->flags &= ~4u;
            selection->choice = -1;
            selection->result = -1;
            selection->message = 204;
            selection->signature_a = 0x9001;
            selection->signature_b = 0x1234;
            selection->state = 33;
            selection->stack[selection->depth++] = 33;
            selection->state = 55;
            selection->stack[selection->depth++] = 55;
            selection->state = 52;
            selection->stack[selection->depth++] = 52;
            selection->state = 54;
            selection->stack[selection->depth++] = 54;
            selection->state = 43;
            selection->stack[selection->depth++] = 43;
            selection->state = 40;
            selection->stack[selection->depth++] = 40;
            selection->state = 57;
            selection->stack[selection->depth++] = 57;
            selection->state = 52;
            selection->stack[selection->depth++] = 52;
            selection->state = 53;
            selection->stack[selection->depth++] = 53;
            selection->state = 66;
        } else {
            struct Selection *selection = gSelection;
            int selected;
            selection->flags &= ~4u;
            /* Keep the observed object base plus word offset; C folds it into
               the literal, changing the complete retail placement. */
            asm volatile("ldr %0, [%1, #4]" : "=r"(selected)
                         : "r"(&gGame.current) : "memory");
            selection->result = selection->choice = selected;
            selection->pending = 16;
            {
                struct Selection *next = gSelection;
                next->signature_a = 0x9001;
                next->signature_b = 0x1234;
                next->message = 195;
            next->state = 36;
            next->stack[next->depth++] = 36;
            next->state = 33;
            next->stack[next->depth++] = 33;
            next->state = 55;
            next->stack[next->depth++] = 55;
            next->state = 52;
            next->stack[next->depth++] = 52;
            next->state = 54;
            next->stack[next->depth++] = 54;
            next->state = 43;
            next->stack[next->depth++] = 43;
            next->state = 40;
            next->stack[next->depth++] = 40;
            next->state = 57;
            next->stack[next->depth++] = 57;
            next->state = 52;
            next->stack[next->depth++] = 52;
            next->state = 53;
            next->stack[next->depth++] = 53;
            next->state = 67;
            }
        }
    }
}
