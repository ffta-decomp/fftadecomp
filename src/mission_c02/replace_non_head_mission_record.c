#include "mission_helpers.h"

struct MissionRecord {
    unsigned mission_id : 10;
    unsigned id_metadata : 6;
    u8 state_flags;
    u8 remaining_ticks;
    u8 unknown_payload[12];
} __attribute__((packed));
struct MissionQueueNode {
    struct MissionRecord *record;
    struct MissionQueueNode *previous;
    struct MissionQueueNode *next;
};
struct MissionRuntime {
    u8 unknown_prefix[0x28c8];
    struct MissionQueueNode *queue_head;
};
typedef char MissionRecordSize[(sizeof(struct MissionRecord) == 16) ? 1 : -1];
typedef char MissionNodeSize[(sizeof(struct MissionQueueNode) == 12) ? 1 : -1];
extern struct MissionRuntime MissionRuntime __asm__("0x02000000");
extern struct MissionRecord MissionRecords[64] __asm__("0x020021c8");
extern struct MissionQueueNode MissionQueuePool[64] __asm__("0x020025c8");
extern const u32 MissionRecordClearCallback __asm__("0x0836d4b8");
extern const u32 MissionRecordCopyCallback __asm__("0x0836d4bc");

u32 ReplaceNonHeadMissionRecord(const struct MissionRecord *source)
{
    struct MissionQueueNode *removed;
    struct MissionQueueNode *previous;
    struct MissionQueueNode *next;
    struct MissionRecord *removed_record;
    struct MissionRecord *free_record;
    struct MissionRecord *scan_record;
    struct MissionQueueNode *free_node;
    s32 pool_index;
    const u32 *clear_callback;

    removed = MissionRuntime.queue_head;
    while (removed->next != 0)
        removed = removed->next;
    while ((previous = removed->previous) != 0) {
        struct MissionRecord *candidate_record;
        u32 state_bits;
        candidate_record = removed->record;
        state_bits = candidate_record->state_flags & 28;
        removed_record = candidate_record;
        if (state_bits != 0)
            break;
        removed = previous;
    }
    if (previous == 0)
        return 0;

    previous->next = removed->next;
    next = removed->next;
    if (next != 0)
        next->previous = removed->previous;
    clear_callback = &MissionRecordClearCallback;
    CallR2Trampoline(removed_record, 16, *clear_callback);
    CallR2Trampoline(removed, 12, *clear_callback);

    pool_index = 0;
    scan_record = MissionRecords;
    for (; pool_index <= 63; ++pool_index, ++scan_record) {
        if (scan_record->mission_id == 0) {
            free_record = scan_record;
            goto copy_record;
        }
    }
    free_record = 0;
copy_record:
    InitializeBattleUnitRecord(free_record, source, 16,
                              MissionRecordCopyCallback);
    {
        s32 node_index;
        node_index = 0;
        free_node = MissionQueuePool;
        for (; node_index <= 63; ++node_index, ++free_node) {
            if (free_node->record == 0)
                goto link_record;
        }
        free_node = 0;
    }
link_record:
    if (MissionRuntime.queue_head != 0) {
        free_node->record = free_record;
        free_node->previous = 0;
        free_node->next = MissionRuntime.queue_head;
        (MissionRuntime.queue_head)->previous = free_node;
        MissionRuntime.queue_head = free_node;
    } else {
        MissionRuntime.queue_head = free_node;
        free_node->record = free_record;
        free_node->next = 0;
        free_node->previous = 0;
    }
    return 1;
}
