#include "../../../src/task_tree_core.h"

struct DefinitionListNode {
    u8 entry_state;
    u8 unknown_01[27];
    u8 list_index;
    u8 unknown_1d[27];
    struct DefinitionListNode *previous;
    struct DefinitionListNode *next;
};
typedef char DefinitionListNodeMustBe64Bytes[
    sizeof(struct DefinitionListNode) == 64 ? 1 : -1];

extern struct DefinitionListNode *gDefinitionObjectList0;
extern struct DefinitionListNode *gDefinitionObjectList1;
extern struct DefinitionListNode *gDefinitionObjectList2;
extern struct DefinitionListNode *gDefinitionObjectList3;

void Source52_00011428(struct DefinitionListNode *node_pointer)
{
    struct DefinitionListNode *node = node_pointer;
    struct DefinitionListNode **head = 0;
    struct DefinitionListNode *previous;
    struct DefinitionListNode *next;

    switch (node->list_index) {
    case 0:
        head = &gDefinitionObjectList0;
        break;
    case 1:
        head = &gDefinitionObjectList1;
        break;
    case 2:
        head = &gDefinitionObjectList2;
        break;
    case 3:
        head = &gDefinitionObjectList3;
        break;
    }

    previous = node->previous;
    next = node->next;
    if (previous != 0)
        previous->next = next;
    else
        *head = next;
    if (next != 0)
        next->previous = previous;
    node->entry_state = 0;
}

asm(".global gDefinitionObjectList0\n.set gDefinitionObjectList0,0x02009178\n"
    ".global gDefinitionObjectList1\n.set gDefinitionObjectList1,0x0200917C\n"
    ".global gDefinitionObjectList2\n.set gDefinitionObjectList2,0x02009174\n"
    ".global gDefinitionObjectList3\n.set gDefinitionObjectList3,0x02009180\n");
