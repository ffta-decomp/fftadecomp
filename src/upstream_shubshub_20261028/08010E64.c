/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010E64.c
 * Original SHA-256: 21f9295c0b63c9fe2ee4e07369cc4476c928f71c8c16bc2881ad5abd05f27901
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node08010E64 {
    u8 state;
    u8 unknown_01[0x1b];
    u8 list;
    u8 unknown_1d[0x1b];
    struct Node08010E64 *previous;
    struct Node08010E64 *next;
} Node08010E64;

extern Node08010E64 *data_02009174[4];

static inline u8 is_finished(Node08010E64 *node)
{
    if (node->state == 2)
        return 1;
    return 0;
}

static inline void remove_node(Node08010E64 *node)
{
    Node08010E64 **head = 0;
    Node08010E64 *previous;
    Node08010E64 *next;

    switch (node->list) {
    case 0:
        head = &data_02009174[1];
        break;
    case 1:
        head = &data_02009174[2];
        break;
    case 2:
        head = &data_02009174[0];
        break;
    case 3:
        head = &data_02009174[3];
        break;
    }
    previous = node->previous;
    next = node->next;
    if (previous != 0)
        previous->next = next;
    else
        *head = next;
    if (next != 0)
        next->previous = previous;
    node->state = 0;
}

/* 0x08010E64 - 204 bytes, including literal pools. */
s16 func_08010E64(Node08010E64 **nodes, u16 count)
{
    s16 i = 0;
    s16 available = 0;

    for (; i < count; i++) {
        if (nodes[i] == 0) {
            available++;
        } else if (is_finished(nodes[i])) {
            remove_node(nodes[i]);
            nodes[i] = 0;
            available++;
        }
    }
    return available;
}
