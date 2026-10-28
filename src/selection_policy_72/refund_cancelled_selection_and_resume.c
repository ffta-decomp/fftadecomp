/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[37];u16 message;u8 gap[4];u32 flags;int choice,result;};
struct Game {u8 gap[0x1f64];u32 currency;};
extern struct Selection *gSelection;
extern struct Game gGame;

asm(".global gSelection\n.set gSelection,0x0200f450\n.global gGame\n.set gGame,0x02000000");
void RefundCancelledSelectionAndResume(void)
{
    struct Selection *selection = gSelection;
    if (selection->result == -1 || selection->choice == -1) {
        selection->message = 184;
        if (selection->flags & 64) {
            gGame.currency += 5000;
            selection->flags &= ~64u;
        }
        gSelection->depth = 0;
        gSelection->state = 47;
    } else {
        selection->state = selection->stack[--selection->depth];
    }
}
