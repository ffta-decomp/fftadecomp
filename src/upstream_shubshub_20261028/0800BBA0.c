/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BBA0.c
 * Original SHA-256: c174178d0aa5c309a3c0eced1f6a33191c661ee77e5cd35c67af8ac1dce1f722
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BBA0..0x0800BBD4: 52 bytes. */
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

void func_0800BBA0(u8 index)
{
    ListNode *node = g_records_02009000[index].head;

    while (node != 0) {
        ListNode *next = node->next;

        if (node->state == 0) {
            node->state = 2;
        }
        node = next;
    }
}
