/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[37];u16 message;u8 gap[4];u32 flags;int choice,result;};
struct Game {u8 gap[0x1f64];u32 currency;};
extern struct Selection *gSelection;
extern struct Game gGame;

asm(".global gSelection\n.set gSelection,0x0200f450");
void PrepareSelectionMessageFlags(void)
{
    struct Selection *selection = gSelection;
    if (selection->message == 187 || selection->message == 204)
        selection->flags |= 4;
    {
        struct Selection *next = gSelection;
        next->flags |= 2;
        next->message = 183;
        next->state = 19;
        next->stack[next->depth++] = 19;
        next->state = 52;
        next->stack[next->depth++] = 52;
        next->state = 53;
    }
}
