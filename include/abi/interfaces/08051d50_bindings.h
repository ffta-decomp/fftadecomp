typedef unsigned char u8;
typedef unsigned int u32;
struct ProgressChoiceSelection { u8 unknown_00[17]; u8 mode; };
struct ProgressChoiceRoot {
    u8 unknown_0000[0xd3c];
    struct ProgressChoiceSelection selection;
    u8 unknown_after_selection[0x1d44 - 0xd3c - sizeof(struct ProgressChoiceSelection)];
    u8 pending_state;
};
typedef char ProgressPendingOffset[((u32)&((struct ProgressChoiceRoot *)0)->pending_state == 0x1d44) ? 1 : -1];
extern struct ProgressChoiceRoot *gProgressChoiceRoot;
extern void PlayProgressChoiceCue(u32);
__asm__(".global gProgressChoiceRoot\n.set gProgressChoiceRoot,0x0200f428\n"
        ".global PlayProgressChoiceCue\n.thumb_set PlayProgressChoiceCue,0x08141541\n");
