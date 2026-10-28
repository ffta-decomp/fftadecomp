typedef unsigned char u8;
typedef unsigned int u32;

struct LinkedNode;
struct ListOwner;
typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);
typedef u32 (*WordCallback)(u32 owner_word, void *argument);

struct ListWordCallbackContext {
    volatile void *argument;
    volatile WordCallback callback;
};

extern void VisitLinkedNodes(const struct ListOwner *owner,
                             ListNodeVisitor visit, void *context);
extern u32 VisitListOwnerWord(struct LinkedNode *node, void *context);
extern u32 CoreRegion30_0009AD1C(u32 owner_word, void *argument);

asm(".global VisitLinkedNodes\n.thumb_set VisitLinkedNodes, 0x080c7cc1\n"
    ".global VisitListOwnerWord\n.thumb_set VisitListOwnerWord, 0x0809abe9\n"
    ".global CoreRegion30_0009AD1C\n.thumb_set CoreRegion30_0009AD1C, 0x0809ad1d\n");

void VisitBattlePhaseOwnerList(u8 *owner_list_record, u32 callback_argument)
{
    struct ListWordCallbackContext context;
    const struct ListOwner *owner;
    u32 argument;
    WordCallback callback;

    argument = (u8)callback_argument;
    callback = CoreRegion30_0009AD1C;
    context.argument = (void *)argument;
    context.callback = callback;
    owner = *(const struct ListOwner * volatile *)(owner_list_record + 16);
    VisitLinkedNodes(owner, VisitListOwnerWord, &context);
}
