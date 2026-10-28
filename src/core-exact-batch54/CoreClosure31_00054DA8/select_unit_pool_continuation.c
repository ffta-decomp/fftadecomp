#include "interfaces.h"

/* The parent consumes these pending states after closing the choice window. */
void SelectUnitPoolContinuation(u8 *flow_state)
{
    struct UnitPoolFlowRoot *root;
    struct UnitPoolSelection *selection;
    PlayUnitPoolCue(100);
    root = gUnitPoolFlowRoot;
    selection = &root->selection;
    switch (selection->mode) {
    case 0:
        *flow_state = 40;
        root->pending_state = 42;
        break;
    case 1:
        *flow_state = 40;
        root->pending_state = 43;
        break;
    case 2:
        *flow_state = 40;
        root->pending_state = 44;
        break;
    }
}
