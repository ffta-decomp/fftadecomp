typedef unsigned int u32;
struct ListOwner;
struct LinkedNode;
typedef u32 (*PayloadCallback)(u32, void *);
struct PayloadVisit { void *argument; PayloadCallback callback; };
struct PayloadContext { u32 unknown[4]; struct ListOwner *owner; };
extern u32 VisitPayloadWord(struct LinkedNode *, const struct PayloadVisit *);
extern void WalkPayloadNodes(const struct ListOwner *, u32 (*)(struct LinkedNode *, const struct PayloadVisit *), const struct PayloadVisit *);
void VisitContextPayloadsAt10(const struct PayloadContext *context,
                              PayloadCallback callback, void *argument)
{
    struct PayloadVisit visit;
    visit.argument = argument;
    visit.callback = callback;
    WalkPayloadNodes(context->owner, VisitPayloadWord, &visit);
}
asm(".thumb_set VisitPayloadWord,0x0809abe9\n");
asm(".thumb_set WalkPayloadNodes,0x080c7cc1\n");
