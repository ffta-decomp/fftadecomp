/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081485AC.c
 * Original SHA-256: 8fe290cb31d798df4d6b3ddd2acd8ce3adf47fbef4ef545500edc3bac5adfbf3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Node {
    u16 state;
    u8 unknown_02[0x26];
    struct Node *next;
} Node;

typedef struct {
    u32 unknown_00;
    Node *head;
} List;

extern List data_03003C60;

/* Complete [0x081485AC, 0x081485D0): 36 bytes, 15 instructions. */
void func_081485AC(void)
{
    Node *node = data_03003C60.head;
    while (node != 0) {
        if (node->state == 2)
            node->state = 1;
        node = node->next;
    }
}
