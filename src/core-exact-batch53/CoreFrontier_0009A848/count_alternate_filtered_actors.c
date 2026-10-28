typedef unsigned char u8;
typedef unsigned int u32;
struct Actor;
struct ListOwner;
struct LinkedNode;
struct ActorCountFilter { u8 count, filters; unsigned short reserved; };
struct ActorListContext { u8 unknown00[24]; struct ListOwner *actors; };
typedef u32 (*ActorCallback)(struct Actor *, struct ActorCountFilter *);
struct WordVisitor { struct ActorCountFilter *argument; ActorCallback callback; };
typedef u32 (*NodeVisitor)(struct LinkedNode *, const struct WordVisitor *);
typedef void (*ClearAllocation)(void *, u32);
extern void VisitActorNodes(const struct ListOwner *, NodeVisitor, struct WordVisitor *);
extern u32 VisitActorNodeWord(struct LinkedNode *, const struct WordVisitor *);
extern u32 CountEligibleActor(struct Actor *, struct ActorCountFilter *);
asm(".global VisitActorNodes\n.thumb_set VisitActorNodes,0x080c7cc1\n.global VisitActorNodeWord\n.thumb_set VisitActorNodeWord,0x0809abe9\n.global CountEligibleActor\n.thumb_set CountEligibleActor,0x08098bb1\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
u8 CountAlternateActorsWithUnitTestFilter(struct ActorListContext *context)
{
    struct ActorCountFilter counter;
    struct WordVisitor visitor;
    ActorCallback callback;
    (*(ClearAllocation *)0x0836d4b8)(&counter, 4);
    counter.filters |= 2;
    callback = CountEligibleActor;
    visitor.argument = &counter;
    visitor.callback = callback;
    VisitActorNodes(context->actors, VisitActorNodeWord, &visitor);
    return counter.count;
}
