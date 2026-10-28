#include "mission_helpers.h"

struct MissionRecord {
    unsigned mission_id : 10;
    unsigned id_metadata : 6;
    unsigned policy_low : 2;
    unsigned status : 3;
    unsigned policy_high : 3;
    u8 remaining_ticks;
    u8 unknown_payload[12];
} __attribute__((packed));

struct MissionQueueNode {
    struct MissionRecord *record;
    struct MissionQueueNode *previous;
    struct MissionQueueNode *next;
};

struct MissionDefinition {
    u8 unknown_prefix[64];
    u8 renewal_ticks;
    u8 unknown_suffix[5];
} __attribute__((packed));

struct MissionRuntime {
    u8 unknown_prefix[0x28c8];
    struct MissionQueueNode *queue_head;
};

typedef char MissionRecordSize[(sizeof(struct MissionRecord) == 16) ? 1 : -1];
typedef char MissionQueueNodeSize[(sizeof(struct MissionQueueNode) == 12) ? 1 : -1];
typedef char MissionDefinitionSize[(sizeof(struct MissionDefinition) == 70) ? 1 : -1];

extern struct MissionRuntime MissionRuntime __asm__("0x02000000");
extern struct MissionQueueNode MissionQueuePool[64] __asm__("0x020025c8");
extern const struct MissionDefinition MissionDefinitions[] __asm__("0x0855ae4c");
extern const u32 MissionRecordClearCallback __asm__("0x0836d4b8");

void AdvanceMissionQueueTimers(void);

void AdvanceMissionQueueTimers(void)
{
    u32 first_count;
    u32 second_count;
    struct MissionQueueNode *iterator;
    struct MissionQueueNode *initial_head;
    struct MissionQueueNode **head;

    first_count = C02_GetCE8A8();
    second_count = C02_GetCED2C();
    if ((u16)first_count == (u16)second_count) {
        u32 completion_flag = 0x5ae;
        if ((u8)GetGameFlag(completion_flag) == 0)
            SetGameFlag(completion_flag, 1);
    }

    if ((u8)GetGameFlag(600) != 0) {
        u32 continuation_flag = 0x48c;
        if ((u8)GetGameFlag(continuation_flag) != 0)
            SetGameFlag(continuation_flag, 1);
    }

    initial_head = MissionRuntime.queue_head;
    if (initial_head == 0)
        return;
    iterator = initial_head;
    head = &MissionRuntime.queue_head;

    do {
        struct MissionRecord *record;
        const struct MissionDefinition *definition;
        struct MissionQueueNode *removed;
        struct MissionQueueNode *previous;
        struct MissionQueueNode *next;
        const u32 *clear_callback;
        s32 status;

        record = iterator->record;
        definition = &MissionDefinitions[record->mission_id];
        if (record->remaining_ticks != 255) {
            if (record->remaining_ticks == 0)
                goto expired;
            --record->remaining_ticks;
        }
        if (record->remaining_ticks != 0)
            goto advance;

expired:
        status = record->status;
        switch (status) {
        case 0:
            if (C02_ExpiredStateZero(record) == 0)
                C02_ExpiredStateFollowup(record, 0);
            /* The source state-zero branch joins the renewal policy. */
        case 1:
        case 2:
        if (definition->renewal_ticks != 0) {
            record->status = 3;
            record->remaining_ticks = definition->renewal_ticks;
            goto advance;
        }

        {
            s32 pool_index = 0;
            struct MissionQueueNode *scan_cursor = MissionQueuePool;
            clear_callback = &MissionRecordClearCallback;
            for (; pool_index <= 63; ++pool_index, ++scan_cursor) {
                if (scan_cursor->record == record) {
                    removed = scan_cursor;
                    goto found_renewal_slot;
                }
            }
            removed = 0;
        }
found_renewal_slot:
        /* A valid pool owner is an original input invariant, not a new guard. */
        previous = removed->previous;
        if (previous != 0)
            goto unlink_after_previous;
        goto unlink_head;

        case 3:
        {
            s32 pool_index = 0;
            struct MissionQueueNode *scan_cursor = MissionQueuePool;
            clear_callback = &MissionRecordClearCallback;
            for (; pool_index <= 63; ++pool_index, ++scan_cursor) {
                if (scan_cursor->record == record) {
                    removed = scan_cursor;
                    goto found_status_three_slot;
                }
            }
            removed = 0;
        }
found_status_three_slot:
        previous = removed->previous;
        if (previous == 0)
            goto unlink_head;
        goto unlink_after_previous;

        default:
            goto advance;
        }

unlink_after_previous:
        next = removed->next;
        previous->next = next;
        if (next == 0)
            goto clear_record;
        next->previous = previous;
        goto clear_record;

unlink_head:
        next = removed->next;
        if (next != 0)
            next->previous = previous;
        *head = next;

clear_record:
        CallR2Trampoline(removed->record, 16, *clear_callback);
        removed->record = 0;

advance:
        iterator = iterator->next;
    } while (iterator != 0);
}
