typedef unsigned int u32;
struct ListOwner;
struct LinkedNode;
typedef u32 (*WordCallback)(u32 word, void *argument);
typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);
struct ListWordCallbackContext {
    void *argument;
    WordCallback callback;
};
struct BattleContextLists {
    u32 unknown_words[6];
    struct ListOwner *payloads_at_18;
};
extern void VisitLinkedNodes(const struct ListOwner *owner,
                            ListNodeVisitor visit, void *context);
extern u32 VisitListOwnerWord(struct LinkedNode *owner, void *context);

void VisitContextPayloadsAt18(const struct BattleContextLists *context,
                             WordCallback callback, void *argument)
{
    struct ListWordCallbackContext visit_context;
    visit_context.argument = argument;
    visit_context.callback = callback;
    VisitLinkedNodes(context->payloads_at_18, VisitListOwnerWord,
                     &visit_context);
}
