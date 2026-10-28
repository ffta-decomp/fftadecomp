/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080105C4.c
 * Original SHA-256: 9c81b9ab4c090eb387e73dd884c217168dbd405d2904d5afe809537326adea7b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node080105C4 {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[6];
    u8 list;
    u8 mode;
    u16 base;
    u16 unknown_20;
    u16 offset;
    u8 unknown_24[10];
    s16 sort_key;
    s8 priority;
    u8 unknown_31[7];
    struct Node080105C4 *previous;
    struct Node080105C4 *next;
} Node080105C4;

extern Node080105C4 *data_02009178;
extern Node080105C4 *data_0200917C;
extern Node080105C4 *data_02009174;
extern Node080105C4 *data_02009180;

static inline u8 uses_priority_only(Node080105C4 *node)
{
    if (node->mode == 0)
        return 1;
    if (node->mode == 1)
        return 1;
    if (node->flags & 0x80)
        return 1;
    return 0;
}

static inline Node080105C4 **get_head(Node080105C4 *node)
{
    Node080105C4 **head = 0;

    switch (node->list) {
    case 0:
        head = &data_02009178;
        break;
    case 1:
        head = &data_0200917C;
        break;
    case 2:
        head = &data_02009174;
        break;
    case 3:
        head = &data_02009180;
        break;
    }
    return head;
}

static inline void insert_priority(Node080105C4 *node, Node080105C4 **head)
{
    s8 priority = node->priority;
    Node080105C4 *current = *head;

    for (;;) {
        if (uses_priority_only(current) && priority >= current->priority) {
            if (current->next == 0) {
                current->next = node;
                node->previous = current;
                node->next = 0;
                return;
            }
            current = current->next;
            continue;
        }
        break;
    }

    if (current != 0) {
        if (current->previous == 0) {
            *head = node;
            node->previous = 0;
        } else {
            current->previous->next = node;
            node->previous = current->previous;
        }
        node->next = current;
        current->previous = node;
    }
}

static inline Node080105C4 *skip_priority_nodes(Node080105C4 *current)
{
    while (uses_priority_only(current)) {
        current = current->next;
        if (current == 0)
            break;
    }
    return current;
}

static inline void insert_key(Node080105C4 *node, Node080105C4 **head)
{
    s16 key = node->sort_key;
    s16 priority = node->priority;
    Node080105C4 *first = *head;
    Node080105C4 *current = skip_priority_nodes(first);
    if (current == 0)
        current = first;

    while (current != 0) {
        if (!uses_priority_only(current)) {
            if (key == current->sort_key) {
                if (priority < current->priority)
                    break;
            } else if (key > current->sort_key) {
                break;
            }
        }
        if (current->next == 0) {
            current->next = node;
            node->previous = current;
            node->next = 0;
            return;
        }
        current = current->next;
    }

    if (current != 0) {
        if (current->previous == 0)
            *head = node;
        else
            current->previous->next = node;
        node->previous = current->previous;
        node->next = current;
        current->previous = node;
    }
}

/* 0x080105C4 - 406 bytes. */
void func_080105C4(Node080105C4 *node)
{
    Node080105C4 **head;

    if (!uses_priority_only(node))
        node->sort_key = node->base + node->offset;

    head = get_head(node);

    if (*head == 0) {
        *head = node;
        return;
    }

    if (uses_priority_only(node)) {
        insert_priority(node, head);
    } else {
        insert_key(node, head);
    }
}
