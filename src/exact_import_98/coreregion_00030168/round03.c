#include "interfaces02.h"

void CommitSelectedLocationFlag(void)
{
    int record_index = gLocationScene->selection->one_based_record;
    u8 *save = gLocationSave;
    struct ShiftedLocationView *record;
    record_index -= 1;
    record = (struct ShiftedLocationView *)(save + record_index * 6);
    if (record->flags.bits.location ==
        ((struct PersistentLocationView *)save)->current.bits.location)
        record->flags.raw |= 0x40;
}
