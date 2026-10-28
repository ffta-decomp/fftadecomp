/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BFC8.c
 * Original SHA-256: 590ac7f30f59e67bd25d8b0d090278b6d083675500c9bc191f1a9b567c3c38d7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node0800BFC8 {
    u8 unknown_00;
    u8 status;
    u8 unknown_02[0x22];
    struct Node0800BFC8 *next;
} Node0800BFC8;

typedef struct {
    Node0800BFC8 *head;
    u8 unknown_04[0x24];
} List0800BFC8;

extern List0800BFC8 data_02009024[];

static inline Node0800BFC8 *list_head(u8 index)
{
    return data_02009024[index].head;
}

void func_0800BFC8(void)
{
    u16 index;

    for (index = 0; index < 2; index++) {
        Node0800BFC8 *node = list_head(index);

        while (node != 0) {
            Node0800BFC8 *next = node->next;

            if (node->status == 2)
                node->status = 0;
            node = next;
        }
    }
}
