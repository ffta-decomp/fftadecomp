/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state;u16 depth;u16 stack[38];u8 unknown;u8 pending;u8 gap[2];u32 flags;};
struct Game {u8 gap[0x1f64];u32 currency;};
extern struct Selection *gSelection;
extern struct Game gGame;
extern u8 gFeedback[];
extern void UpdateChargeFeedback(int,void *,void *,u16,u16);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global gGame\n.set gGame,0x02000000\n.global gFeedback\n.set gFeedback,0x030008b0\n.global UpdateChargeFeedback\n.thumb_set UpdateChargeFeedback,0x8029f19");
void ChargeSelectionFeeAndResume(void)
{
    struct Selection *selection;
    u16 previous;
    gSelection->flags &= ~1u;
    if (gGame.currency > 4999) {
        UpdateChargeFeedback(-5000,gFeedback,0,20,16);
        gGame.currency -= 5000;
        gSelection->flags |= 64;
    }
    gSelection->pending = 48;
    selection = gSelection;
    previous = selection->stack[--selection->depth];
    selection->state = previous;
    selection->stack[selection->depth++] = previous;
    selection->state = 66;
    selection->stack[selection->depth++] = 66;
    selection->state = 55;
}
