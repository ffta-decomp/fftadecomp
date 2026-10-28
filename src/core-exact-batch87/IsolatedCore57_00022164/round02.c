typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct LinkedNode;
struct Container;
struct TreeNode;
struct Record { u16 preceding[9]; u16 order; u8 reserved20[36]; u32 eligible; };
struct Bounds { u16 lower, upper; };
struct SelectionContext { struct Bounds *selection; struct Container *scratch; };
typedef char OrderAt18[(u32)&((struct Record *)0)->order == 18 ? 1 : -1];
typedef char EligibleAt56[(u32)&((struct Record *)0)->eligible == 56 ? 1 : -1];
extern struct Record *ReadNodeRecord(const struct LinkedNode *);
extern struct TreeNode *InsertOrderedRecord(struct Container *, void *, s32);
__asm__(".global ReadNodeRecord\n.thumb_set ReadNodeRecord,0x080c7b75\n.global InsertOrderedRecord\n.thumb_set InsertOrderedRecord,0x080c7ab5");
u32 SelectRecordForIterator(struct LinkedNode *node, struct SelectionContext *context)
{
    struct Record *record = ReadNodeRecord(node);
    struct Bounds *selection = context->selection;
    if (selection->lower <= record->order && selection->upper > record->order && record->eligible != 0)
        /* The insertion site performs its own observed halfword read. */
        InsertOrderedRecord(context->scratch, record, *(volatile u16 *)&record->order);
    return 1;
}
