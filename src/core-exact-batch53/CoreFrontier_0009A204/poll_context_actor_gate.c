typedef unsigned char u8;
typedef unsigned int u32;
struct Actor;
struct ListOwner;
struct LinkedNode;
struct ActorListContext {
    u8 unknown00[16];
    struct ListOwner *actors;
    u8 unknown14[16];
    u32 flags;
};
typedef u32 (*ActorCallback)(struct Actor *, u32 *);
struct WordVisitor { u32 *argument; ActorCallback callback; };
typedef u32 (*NodeVisitor)(struct LinkedNode *, const struct WordVisitor *);
extern void VisitActorNodes(const struct ListOwner *, NodeVisitor, struct WordVisitor *);
extern u32 VisitActorNodeWord(struct LinkedNode *, const struct WordVisitor *);
extern u32 MarkActorByte116(struct Actor *, u32 *);
asm(".global VisitActorNodes\n.thumb_set VisitActorNodes,0x080c7cc1\n.global VisitActorNodeWord\n.thumb_set VisitActorNodeWord,0x0809abe9\n.global MarkActorByte116\n.thumb_set MarkActorByte116,0x0809ac89");
/* The phase remains pending until the context flag enables an all-clear scan. */
u8 PollContextActorGate(struct ActorListContext *context)
{
    u32 pending;
    u8 result;
    struct WordVisitor visitor;
    if (context->flags & 1) {
        ActorCallback callback;
        pending = 0;
        callback = MarkActorByte116;
        visitor.argument = &pending;
        visitor.callback = callback;
        VisitActorNodes(context->actors, VisitActorNodeWord, &visitor);
        result = (u8)pending;
    } else {
        result = 1;
    }
    return result;
}
