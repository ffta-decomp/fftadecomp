/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080D2D54.c
 * Original SHA-256: cff55dbc5e7d9bac68db2e69e2073f6059daa8a8dfbd0ffc0728a670d27ad37c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 unknown_id : 6;
    u8 unknown_flags_low : 2;
    u8 status : 3;
    u8 unknown_flags_high : 3;
} __attribute__((packed)) Record080D2D54;

typedef struct {
    u8 unknown_00[0x41];
    u16 flags;
    u8 unknown_43[3];
} __attribute__((packed)) Metadata080D2D54;

typedef struct Node080D2D54 {
    Record080D2D54 *record;
    u32 unknown_04;
    struct Node080D2D54 *next;
} Node080D2D54;

typedef struct {
    u8 unknown_0000[0x28c8];
    Node080D2D54 *head;
} State080D2D54;

extern State080D2D54 g_state_02000000;
extern const Metadata080D2D54 g_table_0855AE4C[];

/* Target: complete [0x080D2D54, 0x080D2DE0), 140 bytes, 62 instructions. */
Record080D2D54 *func_080D2D54(void)
{
    Node080D2D54 *head = g_state_02000000.head;
    Node080D2D54 *node;

    if (head == 0)
        return 0;
    node = head;
    do {
        u16 id = node->record->id;
        const Metadata080D2D54 *entry = &g_table_0855AE4C[id];

        if ((u16)(id - 0x184) <= 8) {
            Record080D2D54 *record = node->record;
            if (record->status != 3)
                return record;
        }
        if ((entry->flags & 0x1000) != 0) {
            Record080D2D54 *record = node->record;
            if (record->status != 3)
                return record;
        }
        node = node->next;
    } while (node != 0);
    return 0;
}
