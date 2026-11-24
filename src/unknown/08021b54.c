typedef unsigned int u32;
struct ListNode; struct ListOwner;
struct RecordManager { void *pool; struct ListOwner *groups; struct ListOwner *records; };
struct RecordGroup { void *unaccessed_at0; struct ListOwner *records; struct RecordManager *manager; };
typedef u32 (*NodeVisitor)(struct ListNode *, void *);
extern void VisitRecordNodes(const struct ListOwner *, NodeVisitor, void *);
extern u32 RemoveSecondaryMembership(struct ListNode *, void *);
extern u32 ReleaseNodeAllocation(struct ListNode *, void *);
extern void DestroyRecordNodes(struct ListOwner *);
extern struct ListNode *FindGroupNode(struct ListOwner *, u32);
extern void ReleaseGroup(void *, void *);
extern void UnlinkGroupNode(struct ListOwner *, struct ListNode *);
void DestroyRecordGroup(struct RecordGroup *group)
{
    struct RecordManager *manager = group->manager;
    struct ListNode *membership;
    VisitRecordNodes(group->records, RemoveSecondaryMembership, manager->records);
    {
        void *pool = manager->pool;
        VisitRecordNodes(group->records, ReleaseNodeAllocation, pool);
    }
    DestroyRecordNodes(group->records);
    membership = FindGroupNode(manager->groups, (u32)group);
    ReleaseGroup(manager->pool, group);
    UnlinkGroupNode(manager->groups, membership);
}
asm(".global VisitRecordNodes\n.thumb_set VisitRecordNodes,0x080c7cc1\n.global RemoveSecondaryMembership\n.thumb_set RemoveSecondaryMembership,0x08022105\n.global ReleaseNodeAllocation\n.thumb_set ReleaseNodeAllocation,0x080220cd\n.global DestroyRecordNodes\n.thumb_set DestroyRecordNodes,0x080c7909\n.global FindGroupNode\n.thumb_set FindGroupNode,0x080c7bf5\n.global ReleaseGroup\n.thumb_set ReleaseGroup,0x08007171\n.global UnlinkGroupNode\n.thumb_set UnlinkGroupNode,0x080c7a35\n");
