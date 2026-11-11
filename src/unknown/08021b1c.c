typedef unsigned int u32;
struct Container;
struct Owner { void *pool; struct Container *groups; struct Container *scratch; };
struct Group { u32 word0; struct Container *records; struct Owner *owner; u32 word12; };
typedef void (*MemoryClear)(void *, u32);
typedef char GroupSize16[sizeof(struct Group) == 16 ? 1 : -1];
extern void *AllocateGroupMemory(void *, u32);
extern struct Container *CreateGroupContainer(void *);
extern void *AppendOwnerGroup(struct Container *, u32);
__asm__(".global AllocateGroupMemory\n.thumb_set AllocateGroupMemory,0x08007139\n.global CreateGroupContainer\n.thumb_set CreateGroupContainer,0x080c799d\n.global AppendOwnerGroup\n.thumb_set AppendOwnerGroup,0x080c7a75\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
struct Group *CreateBattleRecordGroup(struct Owner *owner)
{
    struct Group *group = AllocateGroupMemory(owner->pool, 16);
    (*(const MemoryClear *)0x0836d4b8)(group, 16);
    group->records = CreateGroupContainer(owner->pool);
    group->owner = owner;
    AppendOwnerGroup(owner->groups, (u32)group);
    return group;
}
