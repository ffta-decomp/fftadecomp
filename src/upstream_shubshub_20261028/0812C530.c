/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812C530.c
 * Original SHA-256: fe0b8dd5c8e184bfe55a5807baef688d3908b8131fb6593c861b16c6a852540c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0812C530..0x0812C56A: 58 bytes. */
typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
} __attribute__((packed)) Item;

typedef struct ItemNode {
    Item *item;
    u32 unknown_04;
    struct ItemNode *next;
} ItemNode;

typedef struct {
    u8 unknown_00[0x28C8];
    ItemNode *head;
} ItemListState;

Item *func_0812C530(const ItemListState *state, u32 id)
{
    ItemNode *head = state->head;
    ItemNode *node;

    if (head == 0)
        return 0;
    for (node = head; node != 0; node = node->next) {
        Item *item = node->item;

        if (item->id == id)
            return item;
    }
    return 0;
}
