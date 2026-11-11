typedef unsigned int u32;
typedef unsigned char u8;

struct LinkedNode;
struct ListOwner;
typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);
typedef u32 (*WordCallback)(u32 owner_word, void *argument);

struct ListWordCallbackContext {
    void *argument;
    WordCallback callback;
};

extern void VisitLinkedNodes(const struct ListOwner *owner,
                             ListNodeVisitor visit, void *context);
extern u32 VisitListOwnerWord(struct LinkedNode *node, void *context);
extern u32 CoreClosure31_0009ACB4(u32 owner_word, void *argument);

asm(".global VisitLinkedNodes\n.thumb_set VisitLinkedNodes, 0x080c7cc1\n"
    ".global VisitListOwnerWord\n.thumb_set VisitListOwnerWord, 0x0809abe9\n"
    ".global CoreClosure31_0009ACB4\n.thumb_set CoreClosure31_0009ACB4, 0x0809acb5\n");

void VisitBattleContinuationOwnerList(u8 *owner_list_record)
{
    struct ListWordCallbackContext context;
    WordCallback callback = CoreClosure31_0009ACB4;
    const struct ListOwner *owner;

    context.argument = 0;
    context.callback = callback;
    owner = *(const struct ListOwner * const *)(owner_list_record + 16);
    VisitLinkedNodes(owner, VisitListOwnerWord, &context);
}
