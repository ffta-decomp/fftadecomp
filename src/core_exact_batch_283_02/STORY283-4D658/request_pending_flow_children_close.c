#include "../../task_tree_core.h"
struct PendingFlowPrefix {
    u8 unknown00;
    u8 close_mask;
    u8 unknown02[26];
    TaskNode *first;
    TaskNode *second;
    TaskNode *third;
};
extern struct PendingFlowPrefix *gPendingFlow;
extern void RequestSelectionTaskClose(TaskNode *task);
asm(".global gPendingFlow\n.set gPendingFlow,0x0201f544\n"
    ".global RequestSelectionTaskClose\n.thumb_set RequestSelectionTaskClose,0x0804e9a1\n");
/* Per-site ownership tests and global reloads after each real close request.
 * The helper marks payload state128; it does not immediately free a node. */
void IsolatedCore57_0004D658(void)
{
    if (gPendingFlow->close_mask & 1) {
        RequestSelectionTaskClose(gPendingFlow->first);
        gPendingFlow->first = 0;
    }
    if (gPendingFlow->close_mask & 2) {
        RequestSelectionTaskClose(gPendingFlow->second);
        gPendingFlow->second = 0;
    }
    if (gPendingFlow->close_mask & 4) {
        RequestSelectionTaskClose(gPendingFlow->third);
        gPendingFlow->third = 0;
    }
}
