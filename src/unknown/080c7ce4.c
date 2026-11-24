typedef unsigned int u32;
struct LinkedNode { u32 word; u32 unknown_04; struct LinkedNode *next; };
struct ListOwner { u32 word; struct LinkedNode *head; };
typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);
__asm__(".global _call_via_r8\n.thumb_set _call_via_r8,0x08142265");
__asm__(".global _call_via_r7\n.thumb_set _call_via_r7,0x08142261");
void VisitLinkedNodesFrom(const struct ListOwner *owner, struct LinkedNode *start,
                         ListNodeVisitor visit, void *context)
    __asm__("CoreClosure31_000C7CE4");
void VisitLinkedNodesFrom(const struct ListOwner *owner, struct LinkedNode *start,
                         ListNodeVisitor visit, void *context)
{
    register void *incoming_context __asm__("r3") = context;
    register struct LinkedNode *start_node __asm__("r5") = start;
    register ListNodeVisitor visitor __asm__("r8");
    void *visitor_context;
    register const struct ListOwner *list_owner __asm__("r6");
    struct LinkedNode *node;
    __asm__("" : "+r"(start_node));
    visitor = visit;
    __asm__("" : "+r"(visitor), "+r"(incoming_context) : "r"(start_node));
    visitor_context = incoming_context;
    __asm__("" : "+r"(visitor_context) : "r"(visitor));
    list_owner = owner;
    __asm__("" : "+r"(list_owner) : "r"(visitor_context));
    node = start_node;
    /* The caller supplies a valid start; callback mutations govern subsequent links. */
    do {
        if (visitor(node, visitor_context) == 0)
            break;
        node = node->next;
        if (node == 0)
            node = list_owner->head;
    } while (start_node != node);
}
