#include "interfaces.h"

/* Byte stores may change the shared root cell; preserve each observed reload. */
void CommitCollectionSelection(u8 *flow_state)
{
    struct CollectionSelection *selection;
    struct CollectionSelection *resolver_selection;
    PlayCollectionCue(100);
    *flow_state = 120;
    gCollectionFlowRoot->pending_state = 40;
    gCollectionFlowRoot->selected_base = gCollectionFlowRoot->list.base;
    selection = &gCollectionFlowRoot->list.selection;
    gCollectionFlowRoot->selected_row = selection->mode;
    resolver_selection = &gCollectionFlowRoot->list.selection;
    gCollectionFlowRoot->selected_index = NormalizeCollectionPosition(
        &gCollectionFlowRoot->list,
        (s8)resolver_selection->mode);
}
