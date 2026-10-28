#include "../../../src/task_tree_core.h"
typedef signed short s16;
struct DefinitionPositionObject {
    u8 unknown_00[20];
    u16 flags;
    u8 unknown_16[6];
    u8 group;
    u8 mode;
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_24[20];
    struct DefinitionPositionObject *previous;
    struct DefinitionPositionObject *next;
};
typedef char DefinitionPositionObjectMustBe64Bytes[sizeof(struct DefinitionPositionObject)==64?1:-1];
extern struct DefinitionPositionObject *gDefinitionObjectList0;
extern struct DefinitionPositionObject *gDefinitionObjectList1;
extern struct DefinitionPositionObject *gDefinitionObjectList2;
extern struct DefinitionPositionObject *gDefinitionObjectList3;
extern void ReinsertDefinitionObject(struct DefinitionPositionObject *);

void SetDefinitionResourceCoordinates(void *object_pointer,u16 x,u16 y,u16 z)
{
    struct DefinitionPositionObject *object = object_pointer;
    u32 changed = 0;
    register u32 direct asm("r0");
    if ((s16)x != object->x || (s16)z != object->z)
        changed = 1;
    object->x = x;
    object->y = y;
    object->z = z;
    {
        register u32 mode asm("r0") = object->mode;
        if (mode == 0)
            direct = 1;
        else {
            /* Preserve the initialized mode at its distinct second comparison. */
            asm("" : : "r" (mode));
            if (mode == 1 || (object->flags & 0x80))
                direct = 1;
            else
                direct = 0;
        }
    }
    /* The native numeric result is materialized before testing the changed flag. */
    asm("" : "+r" (direct));
    if (direct == 0 && changed != 0) {
        struct DefinitionPositionObject **head;
        struct DefinitionPositionObject *previous;
        struct DefinitionPositionObject *next;
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
asm(".global ReinsertDefinitionObject\n.thumb_set ReinsertDefinitionObject,0x080105c5\n"
    ".global gDefinitionObjectList0\n.set gDefinitionObjectList0,0x02009178\n"
    ".global gDefinitionObjectList1\n.set gDefinitionObjectList1,0x0200917c\n"
    ".global gDefinitionObjectList2\n.set gDefinitionObjectList2,0x02009174\n"
    ".global gDefinitionObjectList3\n.set gDefinitionObjectList3,0x02009180\n");
