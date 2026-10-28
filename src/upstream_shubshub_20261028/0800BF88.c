/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BF88.c
 * Original SHA-256: 0498a8b539a25a3dfedf9df6af101091d779611bfa2446f926d38aa0e4365021
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node0800BF88 {
    u8 unknown_00;
    u8 status;
    u8 unknown_02[0x22];
    struct Node0800BF88 *next;
} Node0800BF88;

typedef struct {
    Node0800BF88 *head;
    u8 unknown_04[0x24];
} List0800BF88;

extern List0800BF88 data_02009024[];

static inline Node0800BF88 *list_head(u8 index)
{
    return data_02009024[index].head;
}

void func_0800BF88(void)
{
    u16 index;

    for (index = 0; index < 2; index++) {
        Node0800BF88 *node = list_head(index);

        while (node != 0) {
            Node0800BF88 *next = node->next;

            if (node->status == 0)
                node->status = 2;
            node = next;
        }
    }
}
