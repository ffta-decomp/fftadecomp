/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[32];u8 gap[9];u8 choice_mode;u8 gap78[6];u32 flags;int choice;};
extern struct Selection *gSelection;
extern void ConfigurePane(u8,u8,u8,u8);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global ConfigurePane\n.thumb_set ConfigurePane,0x802a2c1");
void SetSceneSelectionModeFromChoice(void)
{
    struct Selection *selection = gSelection;
    switch (selection->choice) {
    case 1: selection->choice_mode = 4; break;
    case 2: selection->choice_mode = 5; break;
    case 3: selection->choice_mode = 6; break;
    }
    gSelection->flags &= ~2u;
    ConfigurePane(0,0,0,0);
    {
        struct Selection *next = gSelection;
        next->state = 24;
        next->stack[next->depth++] = 24;
        next->state = 49;
    }
}
