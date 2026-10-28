#ifndef SOURCE233_9A9CC_INTERFACES_H
#define SOURCE233_9A9CC_INTERFACES_H

typedef unsigned char u8;
typedef unsigned int u32;

struct ListOwner;
struct LinkedNode;
struct BattlePhaseContext {
    u8 unknown00[16];
    struct ListOwner *list_owner_at_16;
};

typedef u32 (*WordCallback)(u32 word, void *argument);
struct WordVisitor {
    void *argument;
    WordCallback callback;
};
typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);

void VisitLinkedNodes(const struct ListOwner *owner,
                      ListNodeVisitor visit, void *context);
u32 VisitListOwnerWord(struct LinkedNode *node, void *context);
u32 CoreRegion30_0009ADDC(u32 word, void *argument);

#endif
