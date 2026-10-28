#include "interfaces.h"
void ReleaseBothMissionItemReservations(void) __asm__("CoreFrontier_0005DD64");
void ReleaseBothMissionItemReservations(void)
{
    s32 index;
    gMissionReservationClear(gMissionReservations->mission->reserved_items, 2);
    index = 0;
    do {
        struct MissionReservationRecord *record =
            gMissionReservations->items[gMissionReservations->reservation_base + index];
        if (record != 0) {
            record->mission_id = 0;
            record->reservation_flags &= 254;
        }
        index++;
    } while (index <= 1);
}
