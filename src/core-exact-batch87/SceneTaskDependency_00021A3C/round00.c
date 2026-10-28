typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Container;
struct Owner { void *pool; struct Container *groups, *scratch; u16 lower, upper, alternate_lower, alternate_upper; u8 unknown20[460]; u16 flags; u8 unknown482[6]; };
typedef char OwnerSize488[sizeof(struct Owner) == 488 ? 1 : -1];
typedef char FlagsAt480[(u32)&((struct Owner *)0)->flags == 480 ? 1 : -1];
typedef void (*MemoryClear)(void *, u32);
extern void *AllocateOwnerMemory(void *, u32);
extern struct Container *CreateOwnerContainer(void *);
__asm__(".global AllocateOwnerMemory\n.thumb_set AllocateOwnerMemory,0x08007139\n.global CreateOwnerContainer\n.thumb_set CreateOwnerContainer,0x080c799d\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
struct Owner *CreateBattleRecordOwner(void *pool, u16 lower, u16 upper, u16 alternate_lower, u16 alternate_upper)
{
    struct Owner *owner = AllocateOwnerMemory(pool, sizeof(struct Owner));
    (*(const MemoryClear *)0x0836d4b8)(owner, sizeof(struct Owner));
    owner->pool = pool;
    owner->groups = CreateOwnerContainer(pool);
    owner->scratch = CreateOwnerContainer(owner->pool);
    owner->lower = lower;
    owner->upper = upper;
    owner->alternate_lower = alternate_lower;
    owner->alternate_upper = alternate_upper;
    owner->flags = 3;
    return owner;
}
