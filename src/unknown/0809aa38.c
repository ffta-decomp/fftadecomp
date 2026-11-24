typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
struct ActorUnit { u8 unknown00[260]; u8 selector; };
struct Actor { struct ActorUnit *unit; u32 record_word; };
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
/* Preserve the original bounded stack extent; list maximum is not established. */
struct Actor *FindBattleActorByUnitSelector(struct ActorListContext *context,
    u8 selector)
{
    struct Actor *actors[13];
    struct ActorCollection collection;
    struct WordVisitor visitor;
    ActorCallback callback;
    s32 count, index;
    struct Actor **cursor;
    collection.count = 0;
    collection.next = actors;
    callback = AppendActorPointer;
    visitor.argument = &collection;
    visitor.callback = callback;
    VisitActorNodes(context->actors, VisitActorNodeWord, &visitor);
    count = collection.count;
    index = 0;
    if (index < count) {
        u32 selector_offset = (u32)&((struct ActorUnit *)0)->selector;
        cursor = actors;
        do {
        struct Actor *actor = *cursor;
        if (*((u8 *)actor->unit + selector_offset) == selector)
            return actor;
        ++cursor;
        ++index;
        } while (index < count);
    }
    return (struct Actor *)0;
}
