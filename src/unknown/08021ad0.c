typedef unsigned int u32;
typedef u32 (*NodeVisitor)(void *, void *);
struct ActorQueueLists { void *pool; void *primary; void *secondary; };
extern void VisitLinkedNodes(void *, NodeVisitor, void *);
extern u32 ReleaseNodeOwnedContainer(void *, void *);
extern u32 ReleaseNodeAllocation(void *, void *);
extern void *DestroyTreeContainer(void *);
extern void ReleasePoolAllocation(void *, void *);
__asm__(".global VisitLinkedNodes\n.thumb_set VisitLinkedNodes, 0x080c7cc1\n"
        ".global ReleaseNodeOwnedContainer\n.thumb_set ReleaseNodeOwnedContainer, 0x080220b5\n"
        ".global ReleaseNodeAllocation\n.thumb_set ReleaseNodeAllocation, 0x080220cd\n"
        ".global DestroyTreeContainer\n.thumb_set DestroyTreeContainer, 0x080c7909\n"
        ".global ReleasePoolAllocation\n.thumb_set ReleasePoolAllocation, 0x08007171");
void *DestroyActorQueueLists(struct ActorQueueLists *queue)
    __asm__("CoreDependency29_00021AD0");
void *DestroyActorQueueLists(struct ActorQueueLists *queue)
{
    NodeVisitor release_allocation;
    void *final_pool;
    VisitLinkedNodes(queue->primary, ReleaseNodeOwnedContainer, (void *)0);
    {
        register void *visit_pool __asm__("r2") = queue->pool;
        register void *primary_owner __asm__("r0");
        __asm__("" : "+r"(visit_pool));
        primary_owner = queue->primary;
        __asm__("" : "+r"(primary_owner) : "r"(visit_pool));
        release_allocation = ReleaseNodeAllocation;
        VisitLinkedNodes(primary_owner, release_allocation, visit_pool);
    }
    {
        register void *visit_pool __asm__("r2") = queue->pool;
        __asm__("" : "+r"(visit_pool));
        VisitLinkedNodes(queue->secondary, release_allocation, visit_pool);
    }
    DestroyTreeContainer(queue->secondary);
    DestroyTreeContainer(queue->primary);
    final_pool = queue->pool;
    ReleasePoolAllocation(final_pool, queue);
    return final_pool;
}
