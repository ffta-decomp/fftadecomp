/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BB74.c
 * Original SHA-256: 1f2158f30df39dddb47ce8d16781e2c62265a9eaef8b2c1104882887a914e957
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BB74..0x0800BBA0: 44 bytes. */
typedef struct Node0800BB74 {
    u8 unknown_00;
    u8 active;
    u8 unknown_02[0x22];
    struct Node0800BB74 *next;
} Node0800BB74;

typedef struct {
    u8 unknown_00[0x24];
    Node0800BB74 *head;
} Record0800BB74;

extern Record0800BB74 g_records_02009000[];

void func_0800BB74(u8 index)
{
    Node0800BB74 *node = g_records_02009000[index].head;

    while (node != 0) {
        Node0800BB74 *next = node->next;

        node->active = 1;
        node = next;
    }
}
