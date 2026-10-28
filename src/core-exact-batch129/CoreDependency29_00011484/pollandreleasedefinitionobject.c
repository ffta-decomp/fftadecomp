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
struct DefinitionObject *PollAndReleaseDefinitionObject(struct DefinitionObject *object_pointer)
{
    register struct DefinitionObject *pending asm("r1") = object_pointer;
    /* Keep the actual pending-pointer snapshot before its NULL/state query. */
    asm("" : : "r" (pending));
    if (pending != 0) {
        register u32 complete asm("r0");
        if (pending->state == 2)
            complete = 1;
        else
            complete = 0;
        /* Preserve the initialized native numeric predicate before its test. */
        asm("" : "+r" (complete));
        if (complete) {
            register struct DefinitionObject *object asm("r2") = pending;
            struct DefinitionObject **head;
            struct DefinitionObject *previous;
            struct DefinitionObject *next;
            /* This unlink view begins only on the completed branch. */
            asm("" : : "r" (object));
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
            object->state = 0;
            return 0;
        }
    }
    return pending;
}

asm(".global gDefinitionObjectList0\n.set gDefinitionObjectList0,0x2009178\n"
    ".global gDefinitionObjectList1\n.set gDefinitionObjectList1,0x200917c\n"
    ".global gDefinitionObjectList2\n.set gDefinitionObjectList2,0x2009174\n"
    ".global gDefinitionObjectList3\n.set gDefinitionObjectList3,0x2009180\n");
