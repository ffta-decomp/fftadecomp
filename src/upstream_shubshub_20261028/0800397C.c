/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800397C.c
 * Original SHA-256: 484feb9a6c94d9bb1f6de1af92ba78e1beedf94597855dbb83b63f7b3bec055a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Node0800397C {
    struct Node0800397C *next;
    u16 id;
};

extern u8 data_030034D1;
extern u16 data_030034D4;
extern u8 data_030034D0;
extern struct Node0800397C data_030034C0[];
extern struct Node0800397C *data_030034B8;

/* Target: [0x0800397C, 0x080039E8), 108 bytes, 37 instructions. */
void func_0800397C(u8 two_nodes)
{
    data_030034D1 = 0;
    data_030034D4 = 2;
    if (two_nodes != 0) {
        struct Node0800397C *second;

        data_030034D0 = 2;
        data_030034C0[0].next = 0;
        data_030034C0[0].id = 1;
        data_030034B8 = second = &data_030034C0[1];
        second->next = &data_030034C0[0];
        second->id = 2;
    } else {
        data_030034D0 = 1;
        data_030034B8 = &data_030034C0[0];
        data_030034C0[0].next = 0;
        data_030034C0[0].id = 2;
    }
}
