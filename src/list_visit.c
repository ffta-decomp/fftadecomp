typedef unsigned int u32;

struct LinkedNode {
    u32 word;
    u32 unknown_at_04;
    struct LinkedNode *next;
};

struct ListOwner {
    u32 word;
    struct LinkedNode *head;
};

typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);

void VisitLinkedNodes(const struct ListOwner *owner,
                      ListNodeVisitor visit, void *context)
{
    struct LinkedNode *node = owner->head;
    while (node != 0) {
        if (visit(node, context) == 0)
            break;
        node = node->next;
    }
}
