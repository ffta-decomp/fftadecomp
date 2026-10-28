/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800B2A4.c
 * Original SHA-256: 1b68c67d683b5fd5ff166b6cbb6da81c64d5a3448d2af217101abe82d92cf2b9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0800B2A4, 0x0800B394), 240 bytes. */
typedef struct Node0800B2A4 {
    u8 index;
    u8 state;
    u16 flags;
    s16 x;
    s16 y;
    u8 width;
    u8 height;
    u16 field_0a;
    u16 field_0c;
    u16 field_0e;
    u16 field_10;
    u16 unknown_12;
    u32 value_14;
    u32 value_18;
    u8 field_1c;
    u8 field_1d;
    u8 record_width;
    u8 record_height;
    struct Node0800B2A4 *previous;
    struct Node0800B2A4 *next;
} Node0800B2A4;

typedef struct {
    u8 *buffer;
    u32 source;
    u16 format;
    u16 size;
    u8 width;
    u8 height;
    u16 byte_count;
    u16 flags;
    u16 unknown_12;
    u32 field_14;
    s16 x;
    s16 y;
    u8 field_1c;
    u8 unknown_1d;
    u16 field_1e;
    u16 field_20;
    u16 unknown_22;
    Node0800B2A4 *head;
} Record0800B2A4;

extern void *data_02008FF8;
extern Record0800B2A4 g_records_02009000[];
extern void *func_08007138(void *, u32);
extern u32 func_0800AF8C(Node0800B2A4 *);

Node0800B2A4 *func_0800B2A4(u8 index, u32 value_14, u32 value_18,
                           u8 width, u8 height)
{
    Node0800B2A4 *node = func_08007138(data_02008FF8, sizeof(*node));
    Node0800B2A4 **head;
    Node0800B2A4 **heads;
    Record0800B2A4 *records;

    node->state = 0;
    if (!g_records_02009000[index].format)
        node->flags = 0x201;
    else
        node->flags = 2;
    node->flags |= 8;
    node->flags |= 0x200;
    node->index = index;
    node->x = 0;
    node->y = 0;
    node->width = width;
    node->height = height;
    node->field_0a = 0;
    node->field_0e = 0;
    node->field_10 = 0;
    node->value_14 = value_14;
    node->value_18 = value_18;
    node->next = 0;
    node->field_0c = func_0800AF8C(node) - 1;
    node->field_1c = 0;
    node->field_1d = 0;

    records = g_records_02009000;
    node->record_width = records[index].width;
    node->record_height = records[index].height;
    heads = &records[0].head;
    head = (Node0800B2A4 **)((u8 *)heads + index * sizeof(*records));
    if (!*head) {
        *head = node;
        node->previous = 0;
    } else {
        Node0800B2A4 *tail = *head;

        if (tail->next) {
            do {
                tail = tail->next;
            } while (tail->next);
        }
        tail->next = node;
        node->previous = tail;
    }
    g_records_02009000[index].flags |= 2;
    return node;
}
