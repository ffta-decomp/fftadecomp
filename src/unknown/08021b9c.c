typedef unsigned int u32;
struct Container;
struct Owner { void *pool; struct Container *groups, *records; };
struct Group { u32 word0; struct Container *records; struct Owner *owner; u32 word12; };
struct Record { u32 words[18]; };
typedef char RecordSize72[sizeof(struct Record) == 72 ? 1 : -1];
typedef void (*MemoryClear)(void *, u32);
extern void *AllocateRecordMemory(void *, u32);
extern void *AppendRecordPointer(struct Container *, u32);
__asm__(".global AllocateRecordMemory\n.thumb_set AllocateRecordMemory,0x08007139\n.global AppendRecordPointer\n.thumb_set AppendRecordPointer,0x080c7a75\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
struct Record *CreateBattleGroupRecord(struct Group *group)
{
    struct Owner *owner = group->owner;
    struct Record *record = AllocateRecordMemory(owner->pool, 72);
    (*(const MemoryClear *)0x0836d4b8)(record, 72);
    AppendRecordPointer(owner->records, (u32)record);
    AppendRecordPointer(group->records, (u32)record);
    return record;
}
