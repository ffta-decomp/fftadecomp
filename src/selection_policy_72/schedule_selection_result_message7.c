/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Selection {u16 state,depth;u16 stack[37];u16 message;u8 message_mode;u8 gap[11];int result;};
extern struct Selection *gSelection;

asm(".global gSelection\n.set gSelection,0x0200f450");
void ScheduleSelectionResultMessage7(void)
{
    struct Selection *selection = gSelection;
    if (selection->result == -1) {
        struct Selection *next;
        selection->message = 173;
        selection->message_mode = 3;
        next = gSelection;
        next->state = 47;
        next->stack[next->depth++] = 47;
        next->state = 56;
    } else {
        struct Selection *next;
        selection->message = 175;
        selection->message_mode = 7;
        next = gSelection;
        next->state = 15;
        next->stack[next->depth++] = 15;
        next->state = 52;
        next->stack[next->depth++] = 52;
        next->state = 53;
        next->stack[next->depth++] = 53;
        next->state = 56;
    }
}
