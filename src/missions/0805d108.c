#include "missions/interfaces/0805d108_bindings.h"

/* A zero input leaves the first empty slot empty; full sets are unchanged. */
void InsertMissionOperationResult(u16 mission_id)
{
    int slot;
    for (slot = 0; slot < 16; ++slot) {
        if (gMissionResultSet->entries[slot] == 0) {
            gMissionResultSet->entries[slot] = mission_id;
            return;
        }
    }
}
