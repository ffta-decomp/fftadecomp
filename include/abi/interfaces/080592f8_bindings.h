typedef unsigned char u8;
typedef unsigned int u32;
struct CollectionSelection { u8 unknown_00[17]; u8 mode; };
struct CollectionFlowRoot {
    u8 unknown_0000[0xd40];
    struct CollectionSelection selection;
    u8 unknown_after_selection[0x2ca0 - 0xd40 - sizeof(struct CollectionSelection)];
    u8 pending_state;
};
typedef char CollectionPendingOffset[((u32)&((struct CollectionFlowRoot *)0)->pending_state == 0x2ca0) ? 1 : -1];
extern struct CollectionFlowRoot *gCollectionFlowRoot;
extern void PlayCollectionCue(u32);
__asm__(".global gCollectionFlowRoot\n.set gCollectionFlowRoot,0x0200f428\n"
        ".global PlayCollectionCue\n.thumb_set PlayCollectionCue,0x08141541\n");
