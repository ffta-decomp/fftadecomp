/* Method-local interface declarations from the frozen build. */
typedef unsigned short u16;
struct Selection {u16 state,depth;u16 stack[38];};
extern struct Selection *gSelection;

asm(".global gSelection\n.set gSelection,0x0200f450");
void ScheduleSelectionCompletionMessages(void)
{
    struct Selection *selection = gSelection;
    selection->state = 48;
    selection->stack[selection->depth++] = 48;
    selection->state = 57;
    selection->stack[selection->depth++] = 57;
    selection->state = 59;
    selection->stack[selection->depth++] = 59;
    selection->state = 52;
    selection->stack[selection->depth++] = 52;
    selection->state = 53;
}
