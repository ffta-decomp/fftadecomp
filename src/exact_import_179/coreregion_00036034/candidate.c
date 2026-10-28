#include "interfaces.h"

u32 RefreshMissionRecordCollection(u32 mode) __asm__("CoreRegion_00036034");
u32 RefreshMissionRecordCollection(u32 mode)
{
    struct MissionRecord *scratch[16];
    struct MissionRecord **cursor;
    struct MissionRecord *record;
    u32 count;
    u32 identifier;
    int remaining;
    if (mode != 0) {
        {
            struct MissionRecord *empty_record = 0;
            struct MissionRecord **clear_cursor = scratch + 15;
            do {
                *clear_cursor = empty_record;
                --clear_cursor;
            } while ((s32)clear_cursor >= (s32)scratch);
        }
        if (MissionSnapshotsDiffer() != 0) {
            ReloadMissionSnapshotFromSave();
            count = CollectUpdatedMissionRecords(MissionCollectionRoot->state->cached, 16, 1);
        } else {
            count = CollectUpdatedMissionRecords(scratch, 16, 0);
        }
        if (count != 0) {
            cursor = scratch;
            remaining = 15;
            do {
                record = *cursor;
                /* Native ID read precedes the pointer test; preserve its domain. */
                identifier = record->identifier;
                if (identifier != 0 && record != 0)
                    StoreCachedMissionRecord(record);
                ++cursor;
                --remaining;
            } while (remaining >= 0);
        }
        MissionCollectionRoot->state->collected_count = (u8)count;
        return count;
    }
    if (MissionSnapshotsDiffer() == 0 && MissionSnapshotsDiffer() == 0)
        return CollectUpdatedMissionRecords(MissionCollectionRoot->state->cached, 16, 0);
    ReloadMissionSnapshotFromSave();
    return CollectUpdatedMissionRecords(MissionCollectionRoot->state->cached, 16, 1);
}
