#include "interfaces.h"

/* Both branches retain the root captured after the cue call. */
void SelectCollectionContinuation(u8 *flow_state)
{
    struct CollectionFlowRoot *root;
    struct CollectionSelection *selection;
    PlayCollectionCue(100);
    root = gCollectionFlowRoot;
    selection = &root->selection;
    switch (selection->mode) {
    case 0:
        *flow_state = 20;
        root->pending_state = 22;
        break;
    case 1:
        *flow_state = 40;
        root->pending_state = 255;
        break;
    }
}
