#include "interfaces-round02.h"
static inline const struct MissionDefinition *SelectRetentionDefinition(u32 mission_id)
{
    return &gRetentionMissionDefinitions[mission_id];
}
void RetainOrRemoveMissionRecord(struct MissionRecord *record) __asm__("CoreFrontier_000D0ED4");
void RetainOrRemoveMissionRecord(struct MissionRecord *record)
{
    const u8 *retention_ticks;
    DetachMissionAssignments(record, 0);
    retention_ticks = &SelectRetentionDefinition(record->mission_id)->retention_ticks;
    if (*retention_ticks) {
        record->status = 3;
        record->remaining_ticks = *retention_ticks;
    } else {
        s32 index = 0;
        struct MissionNode *cursor = gRetentionMissionNodes;
        void (*const *clear_callback)(void*,u32) = &gRetentionMissionClear;
        struct MissionNode *removed, *previous, *next;
        for (; index <= 63; index++, cursor++) {
            if (cursor->record == record) {
                removed = cursor;
                goto unlink_record;
            }
        }
        /* Retail relies on finding the record; preserve its failure path. */
        removed = 0;
unlink_record:
        previous = removed->previous;
        if (previous) {
            next = removed->next;
            previous->next = next;
            if (next)
                next->previous = previous;
        } else {
            next = removed->next;
            if (next)
                next->previous = previous;
            gRetentionMissionRuntime.head = next;
        }
        (*clear_callback)(removed->record, 16);
        removed->record = 0;
    }
}
