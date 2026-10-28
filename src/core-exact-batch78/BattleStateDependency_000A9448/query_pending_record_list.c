typedef unsigned int u32;
struct ListOwner;
struct LinkedNode;
typedef u32 (*NodeVisitor)(struct LinkedNode *node, void *context);

struct RecordManager {
    unsigned char unknown_before_50[80];
    struct ListOwner *records;
};
extern void VisitRecordNodes(const struct ListOwner *, NodeVisitor, void *);
extern u32 QueryPendingRecordNode(struct LinkedNode *, void *);
__asm__(".global VisitRecordNodes\n.thumb_set VisitRecordNodes, 0x080c7cc1\n"
        ".global QueryPendingRecordNode\n.thumb_set QueryPendingRecordNode, 0x080a95b1");

/* This manager lives in ordinary RAM; the real visitor may set the local flag. */
u32 HasPendingRecord(void) __asm__("BattleStateDependency_000A9448");
u32 HasPendingRecord(void)
{
    struct RecordManager *manager = (struct RecordManager *)0x0200f9e8;
    u32 found = 0;
    VisitRecordNodes(manager->records,
                     QueryPendingRecordNode, &found);
    return found;
}
