#include "interfaces.h"

void RouteInventoryOperationContinuation(u8 *flow_state)
{
    if (ReadInventoryOperationStatus(&gInventoryOperationRoot->operation) == 1) {
        struct InventoryOperationRoot *root = gInventoryOperationRoot;
        u8 previous_state = *flow_state;
        root->resume_state = previous_state;
        *flow_state = 62;
        PlayInventoryOperationCue(104);
    } else {
        *flow_state = 80;
        PlayInventoryOperationCue(105);
    }
}
