/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C1C8.c
 * Original SHA-256: c524f2fb8fbde4b823dd9e846c3db965d26cff4d7f2867f75c1d06f0845a5784
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Allocation0800C1C8 {
    u8 unknown_00[0x24];
    struct Allocation0800C1C8 *next;
};

struct Record0800C1C8 {
    void *allocation;
    u8 unknown_04[0x20];
    struct Allocation0800C1C8 *head;
};

extern void *data_02008FF8;
extern struct Record0800C1C8 g_records_02009000[];
extern void func_08007170(void *allocator, void *allocation);

/* Complete [0x0800C1C8, 0x0800C224): 92 bytes, 39 instructions. */
void func_0800C1C8(u8 index)
{
    struct Allocation0800C1C8 *node = g_records_02009000[index].head;

    while (node != 0) {
        struct Allocation0800C1C8 *next = node->next;

        func_08007170(data_02008FF8, node);
        node = next;
    }
    g_records_02009000[index].head = 0;
    if (g_records_02009000[index].allocation != 0) {
        func_08007170(data_02008FF8, g_records_02009000[index].allocation);
        g_records_02009000[index].allocation = 0;
    }
}
