/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C15C.c
 * Original SHA-256: 916373037fb194feaef24cc52e2c8cd13af301098359460b7fcbc3ed0118c841
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct ResourceTable0800C15C;

extern u32 func_0800AEA0(const struct ResourceTable0800C15C *table);
extern void func_0800ACA8(const struct ResourceTable0800C15C *table, s16 index,
                        u16 *first, u16 *second, u16 *third, u16 *fourth);
extern void func_0800ADD8(const struct ResourceTable0800C15C *table, u16 index,
                        u32 *offset, u16 *first, u16 *second,
                        u16 *third, u16 *fourth);

/* Target: 0x0800C15C..0x0800C1AC, 80 bytes / 35 instructions. */
void func_0800C15C(const struct ResourceTable0800C15C *table,
                   u16 *first, u16 *second)
{
    u16 entry;
    u8 index = func_0800AEA0(table);

    func_0800ACA8(table, index, &entry, 0, 0, 0);
    func_0800ADD8(table, entry & 0x3FFF, 0, first, second, 0, 0);
}
