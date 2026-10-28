#include "interfaces.h"

/* The parent closes the choice before consuming the selected progress state. */
void SelectProgressContinuation(u8 *flow_state)
{
    struct ProgressChoiceRoot *root;
    struct ProgressChoiceSelection *selection;
    PlayProgressChoiceCue(100);
    root = gProgressChoiceRoot;
    selection = &root->selection;
    switch (selection->mode) {
    case 0:
        *flow_state = 200;
        root->pending_state = 254;
        break;
    case 1:
        *flow_state = 200;
        root->pending_state = 180;
        break;
    case 2:
        *flow_state = 100;
        break;
    }
}
