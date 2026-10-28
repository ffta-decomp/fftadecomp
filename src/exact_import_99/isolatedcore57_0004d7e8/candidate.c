#include "contract.h"

/* Discards the currently selected mission-reservation record, then refreshes
 * its inventory list. The caller guarantees a selected record exists. */
void IsolatedCore57_0004D7E8(void)
{
    MissionInventoryRecord *record;
    void *scratch;

    record = GetSelectedMissionRecord();
    record->identity = 0;
    record->flags = 0;
    record->mission_link = 0;
    scratch = AllocateInventoryScratch(100);
    CompactSaveRecordsAndDispatch(scratch);
    FreeInventoryScratch(scratch);
    RefreshInventoryList(4);
}
