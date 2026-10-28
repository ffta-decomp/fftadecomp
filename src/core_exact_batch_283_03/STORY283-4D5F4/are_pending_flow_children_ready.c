#include "../../task_tree_core.h"
struct PendingFlowPrefix {
    u8 unknown00;
    u8 child_mask;
    u8 unknown02[26];
    TaskNode *first;
    TaskNode *second;
    TaskNode *third;
};
extern struct PendingFlowPrefix *gPendingFlow;
extern signed short ReadSelectionTaskCounter(TaskNode *task);
asm(".global gPendingFlow\n.set gPendingFlow,0x0201f544\n"
    ".global ReadSelectionTaskCounter\n.thumb_set ReadSelectionTaskCounter,0x0804e1e1\n");
u32 ArePendingFlowChildrenReady(void) __asm__("IsolatedCore57_0004D5F4");
/* Poll every selected child, even after a prior zero. Each helper may affect
 * the next global owner/mask. The first signed16 value is normalized; later
 * zero values only clear the aggregate. FullwordBoolean, not LOW8 counters. */
u32 ArePendingFlowChildrenReady(void)
{
    u32 ready = 1;
    if (gPendingFlow->child_mask & 1)
        ready = ReadSelectionTaskCounter(gPendingFlow->first) != 0;
    if (gPendingFlow->child_mask & 2) {
        if (ReadSelectionTaskCounter(gPendingFlow->second) == 0)
            ready = 0;
    }
    if (gPendingFlow->child_mask & 4) {
        if (ReadSelectionTaskCounter(gPendingFlow->third) == 0)
            ready = 0;
    }
    return ready;
}
