typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ListNode;
struct Container;
struct TreeNode;
struct Record { u16 preceding[9]; u16 order; };
extern struct Record *ReadRangeNodeRecord(const struct ListNode *);
extern struct TreeNode *InsertRangeRecord(struct Container *, void *, s32);
__asm__(".global ReadRangeNodeRecord\n.thumb_set ReadRangeNodeRecord,0x080c7b75\n.global InsertRangeRecord\n.thumb_set InsertRangeRecord,0x080c7ab5");
u32 InsertListedRecordByOrder(struct ListNode *node, struct Container *container)
{
    struct Record *record = ReadRangeNodeRecord(node);
    InsertRangeRecord(container, record, record->order);
    return 1;
}
