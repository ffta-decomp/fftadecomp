typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct CollectionSelection { u8 unknown_00[17]; s8 mode; };
struct CollectionList {
    u8 unknown_00[24];
    u16 count;
    u16 base;
    u8 unknown_1c[4];
    struct CollectionSelection selection;
};
struct CollectionFlowRoot {
    u8 unknown_0000[0xd20];
    struct CollectionList list;
    u8 unknown_after_list[0x1bba - 0xd20 - sizeof(struct CollectionList)];
    u8 selected_index;
    u8 unknown_1bbb[3];
    u8 selected_base;
    u8 selected_row;
    u8 unknown_1bc0[0x2ca0 - 0x1bc0];
    u8 pending_state;
};
typedef char CollectionListOffset[((u32)&((struct CollectionFlowRoot *)0)->list == 0xd20) ? 1 : -1];
typedef char CollectionIndexOffset[((u32)&((struct CollectionFlowRoot *)0)->selected_index == 0x1bba) ? 1 : -1];
typedef char CollectionPendingOffset[((u32)&((struct CollectionFlowRoot *)0)->pending_state == 0x2ca0) ? 1 : -1];
extern struct CollectionFlowRoot *gCollectionFlowRoot;
extern void PlayCollectionCue(u32);
extern u32 NormalizeCollectionPosition(struct CollectionList *, s8);
__asm__(".global gCollectionFlowRoot\n.set gCollectionFlowRoot,0x0200f428\n"
        ".global PlayCollectionCue\n.thumb_set PlayCollectionCue,0x08141541\n"
        ".global NormalizeCollectionPosition\n.thumb_set NormalizeCollectionPosition,0x08017b69\n");
