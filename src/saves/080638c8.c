/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Selection {u16 state,depth;u16 stack[32];u8 gap[9];u8 choice_mode;};
extern struct Selection *gSelection;
extern void ConfigurePane(u8,u8,u8,u8);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global ConfigurePane\n.thumb_set ConfigurePane,0x802a2c1");
void BeginSceneSelectionMode7(void)
{
    struct Selection *selection;
    gSelection->choice_mode = 7;
    ConfigurePane(0,0,0,0);
    selection = gSelection;
    selection->state = 32;
    selection->stack[selection->depth++] = 32;
    selection->state = 49;
}
