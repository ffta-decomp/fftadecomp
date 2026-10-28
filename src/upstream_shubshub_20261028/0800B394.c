/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800B394.c
 * Original SHA-256: 3f14ebdb10a38b715b2a8c0f23f55fd084a8607b7225df86f3ebd4534729763b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node {
    u8 index;
    u8 status;
    u16 flags;
    u16 field_04;
    u16 field_06;
    u8 selector;
    u8 variant;
    u16 field_0A;
    u16 counter;
    u16 field_0E;
    u16 field_10;
    u8 unknown_12[2];
    s32 x;
    s32 y;
    u8 field_1C;
    u8 field_1D;
    u8 attribute_1E;
    u8 attribute_1F;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[8];
    u16 field_08;
    u8 unknown_0A[2];
    u8 attribute_0C;
    u8 attribute_0D;
    u8 unknown_0E[2];
    u16 flags;
    u8 unknown_12[0x12];
    Node *head;
} NodeTableRecord;

extern void *data_02008FF8;
extern NodeTableRecord g_records_02009000[];
extern void *func_08007138(void *pool, u32 size);
extern u16 func_0800AF8C(Node *node);

/* Target: complete [0x0800B394, 0x0800B47A), 230 bytes. */
Node *func_0800B394(u8 index, s32 x, s32 y, u8 selector, u8 variant)
{
    Node *node = func_08007138(data_02008FF8, sizeof(Node));
    NodeTableRecord *records;
    Node **head;
    u8 *heads;

    node->status = 0;
    if (g_records_02009000[index].field_08 == 0)
        node->flags = 0x201;
    else
        node->flags = 2;
    node->flags |= 4;
    node->index = index;
    node->field_04 = 0;
    node->field_06 = 0;
    node->selector = selector;
    node->variant = variant;
    node->field_0A = 0;
    node->field_0E = 0;
    node->field_10 = 0;
    node->x = x;
    node->y = y;
    node->next = 0;
    node->counter = func_0800AF8C(node) - 1;
    node->field_1C = 0;
    node->field_1D = 0;

    records = g_records_02009000;
    node->attribute_1E = records[index].attribute_0C;
    node->attribute_1F = records[index].attribute_0D;
    heads = (u8 *)records + 0x24;
    head = (Node **)(heads + index * sizeof(NodeTableRecord));
    if (*head == 0)
    {
        *head = node;
        node->previous = 0;
    }
    else
    {
        Node *tail;
        for (tail = *head; tail->next != 0; tail = tail->next)
            ;
        tail->next = node;
        node->previous = tail;
    }
    g_records_02009000[index].flags |= 2;
    g_records_02009000[index].flags |= 0x10;
    return node;
}
