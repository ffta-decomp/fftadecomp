struct ListOwner;
struct ListNode;
struct RecordManager { void *pool; void *unaccessed_at4; struct ListOwner *records; };
struct RecordGroup { void *unaccessed_at0; struct ListOwner *records; struct RecordManager *manager; };
extern struct ListNode *FindRecordNode(struct ListOwner *, unsigned int);
extern void UnlinkRecordNode(struct ListOwner *, struct ListNode *);
extern void ReleaseRecord(void *, void *);
void RemoveRecordMemberships(struct RecordGroup *group, void *record)
{
    struct RecordManager *manager = group->manager;
    struct ListNode *node = FindRecordNode(group->records, (unsigned int)record);
    UnlinkRecordNode(group->records, node);
    node = FindRecordNode(manager->records, (unsigned int)record);
    UnlinkRecordNode(manager->records, node);
    ReleaseRecord(manager->pool, record);
}
asm(".global FindRecordNode\n.thumb_set FindRecordNode,0x080c7bf5\n.global UnlinkRecordNode\n.thumb_set UnlinkRecordNode,0x080c7a35\n.global ReleaseRecord\n.thumb_set ReleaseRecord,0x08007171\n");
