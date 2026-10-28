/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010F30.c
 * Original SHA-256: f213dbfece7f0111c8bfd57cc52bced5ff2efcbbceb9cbaa68b1a71f04dc8049
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08010F30..0x08010FD0: 160 bytes. */
typedef struct Node {
    u8 state;
    u8 unknown_01[0x1B];
    u8 list;
    u8 unknown_1D[0x1B];
    struct Node *previous;
    struct Node *next;
} Node;

extern Node *data_02009174[4];

static inline void remove_node(Node *node)
{
    Node **head = 0;
    Node *previous;
    Node *next;

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
    if (previous)
        previous->next = next;
    else
        *head = next;
    if (next)
        next->previous = previous;
    node->state = 0;
}

void func_08010F30(Node **nodes, u16 count)
{
    s16 index = 0;

    for (; index < count; index++) {
        if (nodes[index]) {
            remove_node(nodes[index]);
            nodes[index] = 0;
        }
    }
}
