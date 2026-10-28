/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SelectionFrame {
    u8 unknown_00[0x1199];
    u8 state;
    u8 unknown_119a;
    u8 action;
    u8 unknown_119c[16];
    u32 selection_words[0];
    u8 unknown_11ac[0x1450-0x11ac];
    u32 selected_word;
};
struct LiveSelection { u32 selected_word; u8 unknown_04[12]; u8 option_a; u8 option_b; u8 option_c; };
typedef char TableOffset[(unsigned)&((struct SelectionFrame *)0)->selection_words==0x11ac?1:-1];
typedef char ChosenOffset[(unsigned)&((struct SelectionFrame *)0)->selected_word==0x1450?1:-1];
extern u32 gSelectionFrameAddress;
extern struct LiveSelection gLiveSelection;
extern u8 gSelectionPanel[];
extern u32 ReadSelectionKind(void);
extern s16 ReadSelectionIndex(void);
extern void UpdateSelectionPanel(void *panel, u32 unused, void *tiles, s16 column, s16 row, u8 enabled);
__asm__(".global gSelectionFrameAddress\n.set gSelectionFrameAddress, 0x0200f448");
__asm__(".global gLiveSelection\n.set gLiveSelection, 0x020020d0");
__asm__(".global gSelectionPanel\n.set gSelectionPanel, 0x030008b0");
__asm__(".global ReadSelectionKind\n.thumb_set ReadSelectionKind, 0x08060dd5");
__asm__(".global ReadSelectionIndex\n.thumb_set ReadSelectionIndex, 0x08060dc5");
__asm__(".global UpdateSelectionPanel\n.thumb_set UpdateSelectionPanel, 0x08029e49");

int ApplySceneSelectionOptions(u8 option_a, u8 option_b, u8 option_c);
int ApplySceneSelectionOptions(u8 option_a, u8 option_b, u8 option_c)
{
    switch ((u8)ReadSelectionKind()) {
    case 1:
    case 2:
        return 1;
    case 3:
    case 4:
    {
        u16 index = (u16)ReadSelectionIndex();
        u32 *reference = &gSelectionFrameAddress;
        struct SelectionFrame *frame = (struct SelectionFrame *)*reference;
        u32 *destination = &frame->selected_word;
        u32 selected = frame->selection_words[index];
        *destination = selected;
        gLiveSelection.selected_word = selected;
        gLiveSelection.option_a = option_a;
        gLiveSelection.option_b = option_b;
        gLiveSelection.option_c = option_c;
        UpdateSelectionPanel(gSelectionPanel, 0, 0, 20, 17, 0);
        ((struct SelectionFrame *)*reference)->action = 5;
        ((struct SelectionFrame *)*reference)->state = 19;
        break;
    }
    }
    return 0;
}
