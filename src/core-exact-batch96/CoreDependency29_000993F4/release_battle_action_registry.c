typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef u32 (*NodeVisitor)(void *, void *);
struct RegistryWorkSlot { void *buffer; u8 unknown_04[12]; };
struct BattleActionRegistry {
    void *pool;
    void *allocation_04;
    void *queue;
    void *allocation_0c;
    void *entities;
    void *container_14;
    void *container_18;
    void *battle_object;
    void *allocation_20;
    u8 unknown_024[880];
    struct RegistryWorkSlot work_slots[2];
};
extern void ReleaseManagedTaskWorkBuffer(void *);
extern void ReleasePoolAllocation(void *, void *);
extern void *DestroyActorQueueLists(void *);
extern void ClearFirstWord(void *);
extern void *DestroyTreeContainer(void *);
extern void VisitLinkedNodes(void *, NodeVisitor, void *);
extern u32 ReleaseRegistryNodePayload(void *, void *);
extern void ClearBattleObjectStateFlag(void *);
__asm__(".global ReleaseManagedTaskWorkBuffer\n.thumb_set ReleaseManagedTaskWorkBuffer, 0x0808f7cd\n"
        ".global ReleasePoolAllocation\n.thumb_set ReleasePoolAllocation, 0x08007171\n"
        ".global DestroyActorQueueLists\n.thumb_set DestroyActorQueueLists, 0x08021ad1\n"
        ".global ClearFirstWord\n.thumb_set ClearFirstWord, 0x0800718d\n"
        ".global DestroyTreeContainer\n.thumb_set DestroyTreeContainer, 0x080c7909\n"
        ".global VisitLinkedNodes\n.thumb_set VisitLinkedNodes, 0x080c7cc1\n"
        ".global ReleaseRegistryNodePayload\n.thumb_set ReleaseRegistryNodePayload, 0x0809ab25\n"
        ".global ClearBattleObjectStateFlag\n.thumb_set ClearBattleObjectStateFlag, 0x0814941d");
void *ReleaseBattleActionRegistry(struct BattleActionRegistry *input)
    __asm__("CoreDependency29_000993F4");
void *ReleaseBattleActionRegistry(struct BattleActionRegistry *input)
{
    register struct BattleActionRegistry *context __asm__("r5") = input;
    register struct RegistryWorkSlot *slot __asm__("r4");
    register s32 remaining __asm__("r6");
    void *final_pool;
    __asm__("" : "+r"(context));
    slot = context->work_slots;
    __asm__("" : "+r"(slot));
    remaining = 1;
    __asm__("" : "+r"(remaining));
    do {
        ReleaseManagedTaskWorkBuffer(slot->buffer);
        slot++;
        remaining--;
    } while (remaining >= 0);
    {
        register void *allocation_pool __asm__("r0") = context->pool;
        /* Native loads the allocator before forming the allocation argument. */
        __asm__("" : "+r"(allocation_pool));
        ReleasePoolAllocation(allocation_pool, context->allocation_20);
    }
    {
        register void *queue_pool __asm__("r0") = DestroyActorQueueLists(context->queue);
        register void *retained_pool __asm__("r4") = queue_pool;
        /* Native retains this initialized return snapshot before its clear. */
        __asm__ volatile("" : "+r"(retained_pool) : "r"(queue_pool));
        ClearFirstWord(queue_pool);
    }
    {
        register void *allocation_pool __asm__("r0") = context->pool;
        /* Native loads the allocator before forming the allocation argument. */
        __asm__("" : "+r"(allocation_pool));
        ReleasePoolAllocation(allocation_pool, context->allocation_04);
    }
    DestroyTreeContainer(context->container_18);
    DestroyTreeContainer(context->container_14);
    VisitLinkedNodes(context->entities, ReleaseRegistryNodePayload, context);
    {
        register void *list_pool __asm__("r0") = DestroyTreeContainer(context->entities);
        register void *retained_pool __asm__("r4") = list_pool;
        __asm__ volatile("" : "+r"(retained_pool) : "r"(list_pool));
        ClearFirstWord(list_pool);
    }
    {
        register void *allocation_pool __asm__("r0") = context->pool;
        /* Native loads the allocator before forming the allocation argument. */
        __asm__("" : "+r"(allocation_pool));
        ReleasePoolAllocation(allocation_pool, context->allocation_0c);
    }
    ClearBattleObjectStateFlag(context->battle_object);
    final_pool = context->pool;
    ReleasePoolAllocation(final_pool, context);
    return final_pool;
}
