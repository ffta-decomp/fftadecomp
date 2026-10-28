#include "turn_selection.h"

/* Retail marker and priority reads are signed halfword loads. */
#define TURN_SIGNED_HALF(p, o) (*(s16 *)((u8 *)(p) + (o)))

struct LinkedNode;
struct ListOwner;
typedef u32 (*NodeVisitor)(struct LinkedNode *, void *);
typedef u32 (*WordVisitor)(u32, void *);
struct WordVisitContext { void *argument; WordVisitor callback; };
struct CollectedNodes { s32 count; void **next; };
extern void VisitLinkedNodes(const struct ListOwner *, NodeVisitor, void *);
extern u32 VisitListOwnerWord(struct LinkedNode *, void *);
extern u32 TurnInitializeOrderMarker(u32, void *);
extern u32 ContentAppendCallback(u32, void *);
extern u32 CollectBattleTurnUnitPointers_0809F78C(const void *, void **, u32);

void SortBattleUnitTurnOrder_08099A70(u8 *context, u8 *current_node)
{
    struct WordVisitContext visitor;
    struct CollectedNodes collected;
    struct WordVisitContext collected_visitor;
    void **nodes;
    s32 next_order;
    s32 index, later;
    s32 count, outer_limit;
    WordVisitor initialize_marker;
    initialize_marker = TurnInitializeOrderMarker;
    visitor.argument = current_node;
    visitor.callback = initialize_marker;
    VisitLinkedNodes((const struct ListOwner *)TURN_WORD(context, 16),
                     VisitListOwnerWord, &visitor);
    nodes = AllocateBattleRecordBlock(80);
    CollectBattleTurnUnitPointers_0809F78C(context, nodes, 20);
    next_order = 0;
    if (current_node != 0) {
        TURN_HALF(current_node, 92) = 0;
        next_order = 1;
    }
    for (index = 0; index < 20; ++index) {
        if (TURN_SIGNED_HALF(nodes[index], 92) == -2)
            TURN_HALF(nodes[index], 92) = next_order++;
    }
    collected.count = 0;
    collected.next = nodes;
    collected_visitor.argument = &collected;
    collected_visitor.callback = ContentAppendCallback;
    VisitLinkedNodes((const struct ListOwner *)TURN_WORD(context, 16),
                     VisitListOwnerWord, &collected_visitor);
    count = collected.count;
    if (next_order < count) {
        outer_limit = count - 1;
        for (index = 0; index < outer_limit; ++index) {
            for (later = index + 1; later < count; ++later) {
                u8 *first = nodes[index];
                u8 *first_unit = (u8 *)TURN_WORD(first, 0);
                s16 *first_priority = (s16 *)(first_unit + 208);
                u8 *second = nodes[later];
                if (*first_priority <
                    TURN_SIGNED_HALF((void *)TURN_WORD(second, 0), 208)) {
                    nodes[index] = second;
                    nodes[later] = first;
                }
            }
        }
        for (index = 0; index < count; ++index) {
            if (TURN_SIGNED_HALF(nodes[index], 92) == -2)
                TURN_HALF(nodes[index], 92) = next_order++;
        }
    }
    ReleaseBattleObject(nodes);
}
