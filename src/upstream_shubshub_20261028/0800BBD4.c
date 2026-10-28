/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BBD4.c
 * Original SHA-256: 8c42ad6a3f9220eeb6f6e745424dedf9a8561c912e068680aea3dcccaa8a6dc4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BBD4..0x0800BC08: 52 bytes / 23 instructions. */
typedef struct ListNode {
    u8 unknown_00;
    u8 state;
    u8 unknown_02[0x22];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 unknown_00[0x24];
    ListNode *head;
} ListRecord;

extern ListRecord g_records_02009000[];

void func_0800BBD4(u8 index)
{
    ListNode *node = g_records_02009000[index].head;

    while (node != 0) {
        ListNode *next = node->next;

        if (node->state == 2)
            node->state = 0;
        node = next;
    }
}
