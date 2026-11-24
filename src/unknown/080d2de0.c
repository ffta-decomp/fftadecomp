typedef unsigned char u8;
typedef unsigned short u16;
struct MissionQueueNode {
    u8 *record;
    struct MissionQueueNode *previous;
    struct MissionQueueNode *next;
};
struct MissionRuntime {
    u8 preceding_data[0x28c8];
    struct MissionQueueNode *queue_head;
};
extern struct MissionRuntime gMissionRuntime;
asm(".global gMissionRuntime\n.set gMissionRuntime,0x02000000");

/* Queue ownership and validity come from the existing mission producer. */
u8 *FindLiveMissionRecord(u16 identifier)
{
    struct MissionQueueNode *head = gMissionRuntime.queue_head;
    struct MissionQueueNode *node;
    u8 *record;
    if (head != (void *)0)
        goto search;
    goto not_found;
found:
    return record;
search:
    node = head;
    do {
        unsigned record_identifier;
        unsigned low_identifier;
        record = node->record;
        low_identifier = record[0];
        record_identifier = record[1];
        record_identifier &= 3;
        record_identifier <<= 8;
        record_identifier |= low_identifier;
        if (record_identifier == identifier)
            goto found;
        node = node->next;
    } while (node != (void *)0);
not_found:
    return (void *)0;
}
