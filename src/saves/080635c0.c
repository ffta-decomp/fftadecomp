/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Selection {u16 state,depth;u16 stack[32];u8 gap[13];u8 pending;u8 gap82[6];int choice,result,previous_choice;u16 signature_a,signature_b;};
extern struct Selection *gSelection;
extern u8 IsSelectionUnavailable(void);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global IsSelectionUnavailable\n.thumb_set IsSelectionUnavailable,0x8061dd1");
void ValidateAndQueueSceneSelection(void)
{
    struct Selection *selection = gSelection;
    selection->previous_choice = selection->choice;
    selection->choice = selection->result;
    if (IsSelectionUnavailable()) {
        struct Selection *invalid = gSelection;
        invalid->choice = -1;
        invalid->result = -1;
    }
    gSelection->pending = 16;
    {
        struct Selection *next = gSelection;
        next->signature_a = 0x9001;
        next->signature_b = 0x1234;
        next->state = 27;
        next->stack[next->depth++] = 27;
        next->state = 55;
        next->stack[next->depth++] = 55;
        next->state = 43;
        next->stack[next->depth++] = 43;
        next->state = 40;
        next->stack[next->depth++] = 40;
        next->state = 57;
    }
}
