#include "interfaces.h"

u32 HasUnreservedMissionItem(void)
{
    struct MissionItemReservation *record = gMissionItemReservations;
    int index;
    for (index = 0; index < 64; ++index, ++record) {
        if (record->item_identity != 0 && record->mission_link == 0)
            return 1;
    }
    return 0;
}
