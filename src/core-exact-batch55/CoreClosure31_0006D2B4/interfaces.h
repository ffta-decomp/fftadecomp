typedef unsigned char u8;
typedef unsigned int u32;
struct InventoryOperation { u8 status; };
struct InventoryOperationRoot {
    u8 unknown_0000[0x1a88];
    struct InventoryOperation operation;
    u8 unknown_after_operation[0x446c - 0x1a88 - sizeof(struct InventoryOperation)];
    u8 resume_state;
};
typedef char InventoryResumeOffset[((u32)&((struct InventoryOperationRoot *)0)->resume_state == 0x446c) ? 1 : -1];
extern struct InventoryOperationRoot *gInventoryOperationRoot;
extern u8 ReadInventoryOperationStatus(const struct InventoryOperation *);
extern void PlayInventoryOperationCue(u32);
__asm__(".global gInventoryOperationRoot\n.set gInventoryOperationRoot,0x0200f428\n"
        ".global ReadInventoryOperationStatus\n.thumb_set ReadInventoryOperationStatus,0x0806fe15\n"
        ".global PlayInventoryOperationCue\n.thumb_set PlayInventoryOperationCue,0x08141541\n");
