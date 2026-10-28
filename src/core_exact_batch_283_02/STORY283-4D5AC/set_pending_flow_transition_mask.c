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
extern void RequestSelectionTaskPhase64(TaskNode *task);
asm(".global gPendingFlow\n.set gPendingFlow,0x0201f544\n"
    ".global RequestSelectionTaskPhase64\n.thumb_set RequestSelectionTaskPhase64,0x0804e9b1\n");
/* Store the incoming byte including its upper bits. Each child request can
 * affect the global owner/mask used by the following independent phase.
 * The real helper clears its counter then requests state64; no pointer clear. */
void CoreRegion_0004D5AC(u8 mask)
{
    gPendingFlow->child_mask = mask;
    if (gPendingFlow->child_mask & 1)
        RequestSelectionTaskPhase64(gPendingFlow->first);
    if (gPendingFlow->child_mask & 2)
        RequestSelectionTaskPhase64(gPendingFlow->second);
    if (gPendingFlow->child_mask & 4)
        RequestSelectionTaskPhase64(gPendingFlow->third);
}
