typedef unsigned int u32;
struct ListOwner;
struct LinkedNode;
struct FlagRecord;
struct FlagUpdate { u32 clear_mask; u32 set_mask; };
struct RecordListOwner { unsigned char unknown[16]; struct ListOwner *list; };
typedef u32 (*WordCallback)(struct FlagRecord *,const struct FlagUpdate *);
struct WordVisitContext { const struct FlagUpdate *argument; WordCallback callback; };
extern u32 UpdateVisitedRecordFlags(struct FlagRecord *,const struct FlagUpdate *);
extern u32 VisitListOwnerWord(struct LinkedNode *,void *);
extern void VisitLinkedNodes(struct ListOwner *,u32 (*)(struct LinkedNode *,void *),void *);
__asm__(".global UpdateVisitedRecordFlags\n.thumb_set UpdateVisitedRecordFlags,0x0809aca5\n.global VisitListOwnerWord\n.thumb_set VisitListOwnerWord,0x0809abe9\n.global VisitLinkedNodes\n.thumb_set VisitLinkedNodes,0x080c7cc1");
void UpdateOwnerRecordFlags(struct RecordListOwner *owner,u32 clear_mask,u32 set_mask) __asm__("BattleStateDependency_0009A548");
void UpdateOwnerRecordFlags(struct RecordListOwner *owner,u32 clear_mask,u32 set_mask)
{
    struct FlagUpdate update;
    struct WordVisitContext context;
    update.clear_mask = clear_mask;
    update.set_mask = set_mask;
    {
    register WordCallback callback __asm__("r1") = UpdateVisitedRecordFlags;
    /* Original callback literal lives in r1 before constructing the argument pointer. */
    __asm__("" : "+r"(callback));
    context.argument = &update;
    context.callback = callback;
    }
    VisitLinkedNodes(owner->list,VisitListOwnerWord,&context);
}
