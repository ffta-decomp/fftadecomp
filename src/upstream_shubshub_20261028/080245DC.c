/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080245DC.c
 * Original SHA-256: d7cb2ade6532f6aaf4bfa68ac87e5f913d64cbcaaeef847788e72713a746b121
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080245DC, 0x08024670), 148 bytes. */
typedef struct {
    u8 unknown_00[7];
    u8 flags;
} InputState;

typedef struct {
    u16 unknown_00;
    u8 count;
    u8 index;
    u32 unknown_04;
    u32 *words;
    u8 *flags;
} TableSlot;

extern InputState data_03000000;
extern TableSlot data_03002710;
extern TableSlot data_030027E0;
extern void *data_03002778;
extern u32 data_03000E54;
extern void func_08006BE0(TableSlot *table, u8 index);
extern void func_08022E24(void);
extern void func_0801DB78(void);
extern void *func_08022840(u32 size);

void func_080245DC(u8 reset)
{
    TableSlot *table;

    data_03000000.flags &= 0xfe;
    table = &data_03002710;
    table->index = 0;
    func_08006BE0(table, 0);
    func_08006BE0(table, 3);
    func_08006BE0(table, 4);
    func_08006BE0(table, 2);
    func_08006BE0(table, 5);
    func_08006BE0(table, 6);
    func_08006BE0(table, 7);
    data_030027E0.index = 0;
    func_08006BE0(&data_030027E0, 0);
    if (reset) {
        func_08022E24();
        func_0801DB78();
    }
    {
        void **buffer = &data_03002778;
        u32 size = 0xc600;

        *buffer = func_08022840(size);
        data_03000E54 = size;
    }
}
