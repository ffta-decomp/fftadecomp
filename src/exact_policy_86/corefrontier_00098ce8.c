/* Method-local interface declarations from the frozen build. */
#ifndef BATTLE_MEMBERSHIP_REBUILD_INTERFACES_H
#define BATTLE_MEMBERSHIP_REBUILD_INTERFACES_H
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct LinkedNode;
struct ListOwner;
struct MembershipContext {
    u8 unknown00[16];
    struct ListOwner *primary;
    struct ListOwner *ordinary;
    struct ListOwner *alternate;
};
struct BattleNode {
    u8 *unit;
    u8 unknown04[32];
    u32 key;
    u8 unknown28[88];
    struct MembershipContext *owner;
};
typedef u32 (*NodeVisitor)(struct LinkedNode *, void *);
typedef u32 (*WordVisitor)(struct BattleNode *, void *);
struct CollectedNodes { s32 count; struct BattleNode **next; };
struct WordVisitContext { void *argument; WordVisitor callback; };
extern void VisitLinkedNodes(struct ListOwner *, NodeVisitor, void *);
extern u32 VisitListOwnerWord(struct LinkedNode *, void *);
extern u32 ContentAppendCallback(struct BattleNode *, void *);
extern void RemoveBattleNodeMemberships(struct BattleNode *);
extern struct LinkedNode *FindMember(struct ListOwner *, struct BattleNode *);
extern struct LinkedNode *AppendMember(struct ListOwner *, struct BattleNode *);
extern void *InsertKeyedMember(struct ListOwner *, struct BattleNode *, u32);
extern u32 TestUnitCondition8298(u8 *);
extern u32 TestUnitCondition8240(u8 *);
asm(".global VisitLinkedNodes\n.thumb_set VisitLinkedNodes,0x080c7cc1\n"
    ".global VisitListOwnerWord\n.thumb_set VisitListOwnerWord,0x0809abe9\n"
    ".global ContentAppendCallback\n.thumb_set ContentAppendCallback,0x0809ac21\n"
    ".global RemoveBattleNodeMemberships\n.thumb_set RemoveBattleNodeMemberships,0x080971f9\n"
    ".global FindMember\n.thumb_set FindMember,0x080c7bf5\n"
    ".global AppendMember\n.thumb_set AppendMember,0x080c7a75\n"
    ".global InsertKeyedMember\n.thumb_set InsertKeyedMember,0x080c7ab5\n"
    ".global TestUnitCondition8298\n.thumb_set TestUnitCondition8298,0x080c8299\n"
    ".global TestUnitCondition8240\n.thumb_set TestUnitCondition8240,0x080c8241\n");
typedef char CheckNodeLayout[(sizeof(struct BattleNode)==132)?1:-1];
#endif


void RebuildBattleUnitMembershipLists(struct MembershipContext *context)
{
    struct BattleNode *nodes[13];
    struct CollectedNodes collected;
    struct WordVisitContext visitor;
    WordVisitor append;
    s32 count, index, later, outer_limit;
    collected.count = 0;
    collected.next = nodes;
    append = ContentAppendCallback;
    visitor.argument = &collected;
    visitor.callback = append;
    VisitLinkedNodes(context->primary, VisitListOwnerWord, &visitor);
    count = collected.count;
    for (index = 0; index < count; ++index)
        RemoveBattleNodeMemberships(nodes[index]);
    index = 0;
    outer_limit = count - 1;
    for (; index < outer_limit; ++index) {
        for (later = index + 1; later < count; ++later) {
            struct BattleNode *first = nodes[index];
            u8 *first_priority = first->unit + 260;
            struct BattleNode *second = nodes[later];
            if (*first_priority >= second->unit[260]) {
                nodes[index] = second;
                nodes[later] = first;
            }
        }
    }
    for (index = 0; index < count; ++index) {
        struct BattleNode *node;
        struct MembershipContext **owner;
        if ((u8)TestUnitCondition8298(nodes[index]->unit)) {
            node = nodes[index];
            owner = &node->owner;
            if (FindMember((*owner)->primary, node) == 0) {
                AppendMember((*owner)->primary, node);
                InsertKeyedMember((*owner)->primary, node, node->key);
            }
        } else if ((u8)TestUnitCondition8240(nodes[index]->unit)) {
            node = nodes[index];
            owner = &node->owner;
            if (FindMember((*owner)->primary, node) == 0) {
                AppendMember((*owner)->primary, node);
                InsertKeyedMember((*owner)->primary, node, node->key);
            }
            if (FindMember((*owner)->alternate, node) == 0) {
                AppendMember((*owner)->alternate, node);
                InsertKeyedMember((*owner)->alternate, node, node->key);
            }
        } else {
            node = nodes[index];
            owner = &node->owner;
            if (FindMember((*owner)->primary, node) == 0) {
                AppendMember((*owner)->primary, node);
                InsertKeyedMember((*owner)->primary, node, node->key);
            }
            if (FindMember((*owner)->ordinary, node) == 0) {
                AppendMember((*owner)->ordinary, node);
                InsertKeyedMember((*owner)->ordinary, node, node->key);
            }
        }
    }
}
