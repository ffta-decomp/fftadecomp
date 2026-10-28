/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[38];u8 unknown80,pending;u8 gap[6];u32 choice;u8 gap92[8];u16 signature_a,signature_b;};
struct Game {u8 gap[0x1f6b];u8 active_slot;u8 gap2[0x3c28-0x1f6c];u16 content_choice;};
extern struct Selection *gSelection;
extern struct Game gGame;
extern void PrepareContentChoice(u8);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global gGame\n.set gGame,0x02000000\n.global PrepareContentChoice\n.thumb_set PrepareContentChoice,0x802da01");
void BeginSelectionChoiceZeroContinuation(void)
{
    struct Selection *selection;
    gSelection->choice = 0;
    gSelection->pending = 16;
    selection = gSelection;
    selection->signature_a = 0x9003;
    selection->signature_b = 0x1236;
    selection->state = 1;
    selection->stack[selection->depth++] = 1;
    selection->state = 18;
    selection->stack[selection->depth++] = 18;
    selection->state = 46;
    selection->stack[selection->depth++] = 46;
    selection->state = 40;
    selection->stack[selection->depth++] = 40;
    selection->state = 57;
}
