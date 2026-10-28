#include "../../../src/task_tree_core.h"
/* Prefix only: the remaining record and the marker's game meaning are unknown. */
struct SaveSummaryQueueRecord {
    u16 marker_id : 10;
    u16 : 6;
} __attribute__((packed));
struct SaveSummaryQueueNode {
    struct SaveSummaryQueueRecord *record;
    u32 unknown_04;
    struct SaveSummaryQueueNode *next;
};
struct SaveSummaryQueueView {
    u8 unknown_prefix[0x28c8];
    struct SaveSummaryQueueNode *summary_queue;
};
typedef char QueueRecordPrefixSize[sizeof(struct SaveSummaryQueueRecord) == 2 ? 1 : -1];
u32 HasSaveSummaryQueueMarker(u8 *image)
{
    struct SaveSummaryQueueNode *head = ((struct SaveSummaryQueueView *)image)->summary_queue;
    struct SaveSummaryQueueNode *node;
    if (head != 0)
        goto scan;
    goto missing;
found:
    return 1;
scan:
    node = head;
    do {
        if (node->record->marker_id == 0x17f)
            goto found;
        node = node->next;
    } while (node != 0);
missing:
    return 0;
}
