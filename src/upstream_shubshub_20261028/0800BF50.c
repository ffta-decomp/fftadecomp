/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BF50.c
 * Original SHA-256: 8b86bd1608e7d221808308151708b0babac2397e9888799f94c1785edde89fbf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node0800BF50 {
    u8 unknown_00;
    u8 status;
    u8 unknown_02[0x22];
    struct Node0800BF50 *next;
} Node0800BF50;

typedef struct {
    Node0800BF50 *head;
    u8 unknown_04[0x24];
} List0800BF50;

extern List0800BF50 data_02009024[];

static inline Node0800BF50 *list_head(u8 index)
{
    return data_02009024[index].head;
}

/* 0800BF50..0800BF88: 56 bytes. */
void func_0800BF50(void)
{
    u16 index;

    for (index = 0; index < 2; index++) {
        Node0800BF50 *node = list_head(index);

        while (node != 0) {
            Node0800BF50 *next = node->next;

            node->status = 1;
            node = next;
        }
    }
}
