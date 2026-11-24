typedef unsigned char u8;
typedef unsigned int u32;
struct InventorySelection { u8 unknown_00[17]; u8 mode; };
struct InventoryFlowRoot {
    u8 unknown_0000[0xf3c];
    struct InventorySelection selection;
    u8 unknown_after_selection[0x2ca0 - 0xf3c - sizeof(struct InventorySelection)];
    u8 pending_state;
};
typedef char InventoryPendingOffset[((u32)&((struct InventoryFlowRoot *)0)->pending_state == 0x2ca0) ? 1 : -1];
extern struct InventoryFlowRoot *gInventoryFlowRoot;
extern void PlayInventoryCue(u32);
extern u32 HasNonzeroExtensionInventoryCount(void);
__asm__(".global gInventoryFlowRoot\n.set gInventoryFlowRoot,0x0200f428\n"
        ".global PlayInventoryCue\n.thumb_set PlayInventoryCue,0x08141541\n"
        ".global HasNonzeroExtensionInventoryCount\n.thumb_set HasNonzeroExtensionInventoryCount,0x08058c0d\n");
