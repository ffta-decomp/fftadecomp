#include "interfaces.h"

/* The inventory predicate may replace the root; reload it after querying. */
void SelectInventoryContinuation(u8 *flow_state)
{
    struct InventoryFlowRoot *root;
    struct InventorySelection *selection;
    PlayInventoryCue(100);
    root = gInventoryFlowRoot;
    selection = &root->selection;
    switch (selection->mode) {
    case 0:
        if ((u8)HasNonzeroExtensionInventoryCount() != 0) {
            *flow_state = 65;
            gInventoryFlowRoot->pending_state = 254;
        } else {
            *flow_state = 65;
            gInventoryFlowRoot->pending_state = 69;
        }
        break;
    case 1:
        *flow_state = 65;
        root->pending_state = 80;
        break;
    }
}
