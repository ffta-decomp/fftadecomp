typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
struct Actor { void *unit; u32 record_word; };
struct ListOwner;
struct LinkedNode;
struct ActorListContext { u8 unknown00[16]; struct ListOwner *actors; };
struct ActorCollection { s32 count; struct Actor **next; };
typedef u32 (*ActorCallback)(struct Actor *, struct ActorCollection *);
struct WordVisitor { struct ActorCollection *argument; ActorCallback callback; };
typedef u32 (*NodeVisitor)(struct LinkedNode *, const struct WordVisitor *);
extern void VisitActorNodes(const struct ListOwner *, NodeVisitor, struct WordVisitor *);
extern u32 VisitActorNodeWord(struct LinkedNode *, const struct WordVisitor *);
extern u32 AppendActorPointer(struct Actor *, struct ActorCollection *);
asm(".global VisitActorNodes\n.thumb_set VisitActorNodes,0x080c7cc1\n.global VisitActorNodeWord\n.thumb_set VisitActorNodeWord,0x0809abe9\n.global AppendActorPointer\n.thumb_set AppendActorPointer,0x0809ac21");
/* Thirteen pointers is the original stack extent, not a proven list maximum. */
void ClearCollectedBattleActorRecords(struct ActorListContext *context)
{
    struct Actor *actors[13];
    struct ActorCollection collection;
    struct WordVisitor visitor;
    ActorCallback callback;
    collection.count = 0;
    collection.next = actors;
    callback = AppendActorPointer;
    visitor.argument = &collection;
    visitor.callback = callback;
    VisitActorNodes(context->actors, VisitActorNodeWord, &visitor);
    if (collection.count > 0) {
        u32 cleared_record = 0;
        struct Actor **cursor = actors;
        s32 remaining = collection.count;
        do {
            struct Actor *actor = *cursor++;
            actor->record_word = cleared_record;
        } while (--remaining != 0);
    }
}
