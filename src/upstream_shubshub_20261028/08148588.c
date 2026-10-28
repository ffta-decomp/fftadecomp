/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148588.c
 * Original SHA-256: 3b522545410eb7eb452613954b4887f456e9481954763dd74fd31e4eab680ef0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08148588..0x081485AC: 36 bytes. */
typedef struct StateNode {
    u16 status;
    u8 unknown_02[0x26];
    struct StateNode *next;
} StateNode;

typedef struct {
    u32 unknown_00;
    StateNode *head;
} StateList;

extern StateList data_03003C60;

void func_08148588(void)
{
    StateNode *node = data_03003C60.head;

    while (node != 0) {
        if (node->status == 1)
            node->status = 2;
        node = node->next;
    }
}
