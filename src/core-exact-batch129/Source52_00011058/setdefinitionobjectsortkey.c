#include "../../../src/task_tree_core.h"

typedef signed short s16;

struct DefinitionObject {
    u8 state;
    u8 unknown_01[27];
    u8 group;
    u8 unknown_1d[11];
    u8 option;
    u8 unknown_29[7];
    signed char sort_key;
    u8 unknown_31[7];
    struct DefinitionObject *previous;
    struct DefinitionObject *next;
};
typedef char DefinitionObjectMustBe64Bytes[sizeof(struct DefinitionObject)==64?1:-1];
extern struct DefinitionObject *gDefinitionObjectList0;
extern struct DefinitionObject *gDefinitionObjectList1;
extern struct DefinitionObject *gDefinitionObjectList2;
extern struct DefinitionObject *gDefinitionObjectList3;
extern void ReinsertDefinitionObject(struct DefinitionObject *);
void SetDefinitionObjectSortKey(void *object_pointer, s16 key)
{
    struct DefinitionObject *object = object_pointer;
    if (object->sort_key != key) {
        struct DefinitionObject **head;
        struct DefinitionObject *previous;
        struct DefinitionObject *next;
        object->sort_key = key;
        head = 0;
        switch (object->group) {
        case 0: head = &gDefinitionObjectList0; break;
        case 1: head = &gDefinitionObjectList1; break;
        case 2: head = &gDefinitionObjectList2; break;
        case 3: head = &gDefinitionObjectList3; break;
        }
        previous = object->previous;
        next = object->next;
        if (previous != 0)
            previous->next = next;
        else
            *head = next;
        if (next != 0)
            next->previous = previous;
        ReinsertDefinitionObject(object);
    }
}

asm(".global ReinsertDefinitionObject\n.thumb_set ReinsertDefinitionObject,0x80105c5\n"
    ".global gDefinitionObjectList0\n.set gDefinitionObjectList0,0x2009178\n"
    ".global gDefinitionObjectList1\n.set gDefinitionObjectList1,0x200917c\n"
    ".global gDefinitionObjectList2\n.set gDefinitionObjectList2,0x2009174\n"
    ".global gDefinitionObjectList3\n.set gDefinitionObjectList3,0x2009180\n");
