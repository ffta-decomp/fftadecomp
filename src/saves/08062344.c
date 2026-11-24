/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Selection {u16 state,depth;u16 stack[37];u16 message;};
struct Game {u8 gap[114];u8 live_save;};
extern struct Selection *gSelection;
extern struct Game gGame;

asm(".global gSelection\n.set gSelection,0x0200f450\n.global gGame\n.set gGame,0x02000000");
void ScheduleInitialSaveSelectionMessage(void)
{
    if (gGame.live_save) {
        struct Selection *selection = gSelection;
        selection->message = 202;
        selection->state = 2;
        selection->stack[selection->depth++] = 2;
        selection->state = 49;
        selection->stack[selection->depth++] = 49;
    selection->state = 52;
    selection->stack[selection->depth++] = 52;
    selection->state = 51;
    } else {
        struct Selection *selection = gSelection;
        selection->message = 201;
        selection->state = 1;
        selection->stack[selection->depth++] = 1;
    selection->state = 52;
    selection->stack[selection->depth++] = 52;
    selection->state = 51;
    }
}
