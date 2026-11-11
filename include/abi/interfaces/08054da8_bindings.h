typedef unsigned char u8;
typedef unsigned int u32;
struct UnitPoolSelection { u8 unknown_00[17]; u8 mode; };
struct UnitPoolFlowRoot {
    u8 unknown_0000[0x14dc];
    struct UnitPoolSelection selection;
    u8 unknown_after_selection[0x2d38 - 0x14dc - sizeof(struct UnitPoolSelection)];
    u8 pending_state;
};
typedef char UnitPoolPendingOffset[((u32)&((struct UnitPoolFlowRoot *)0)->pending_state == 0x2d38) ? 1 : -1];
extern struct UnitPoolFlowRoot *gUnitPoolFlowRoot;
extern void PlayUnitPoolCue(u32);
__asm__(".global gUnitPoolFlowRoot\n.set gUnitPoolFlowRoot,0x0200f428\n"
        ".global PlayUnitPoolCue\n.thumb_set PlayUnitPoolCue,0x08141541\n");
