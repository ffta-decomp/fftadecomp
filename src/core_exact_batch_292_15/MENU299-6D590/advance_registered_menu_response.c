#include "../../task_tree_core.h"

extern u8 *MenuResponseWorkspace;
extern u32 ReadMenuResponseState(const void *state);
extern void RequestMenuResponseDefinition(u32 index);

void CoreClosure31_0006D590(u8 *controller_state)
{
    register u8 *first_destination asm("r4") = controller_state;
    register u8 *second_destination asm("r6") = first_destination;
    register u8 **workspace_cell asm("r5") = &MenuResponseWorkspace;
    /* Keep the original cell address, not a snapshot of its loaded workspace. */
    asm("" : "+r"(workspace_cell));
    /* Original entry retains both initialized destination aliases across calls. */
    asm("" : "+r"(first_destination), "+r"(second_destination));
    if ((u8)ReadMenuResponseState(*workspace_cell + 0x1a88) == 4) {
        RequestMenuResponseDefinition(100);
        *first_destination = 60;
    } else {
        /* The original queries again through a freshly loaded workspace. */
        if ((u8)ReadMenuResponseState(*workspace_cell + 0x1a88) != 1)
            return;
        RequestMenuResponseDefinition(104);
        *second_destination = 62;
    }
    (*workspace_cell)[0x446c] = 23;
}

asm(".global MenuResponseWorkspace\n.set MenuResponseWorkspace,0x0200f428\n"
    ".global ReadMenuResponseState\n.thumb_set ReadMenuResponseState,0x0806fe15\n"
    ".global RequestMenuResponseDefinition\n.thumb_set RequestMenuResponseDefinition,0x08141541\n");
