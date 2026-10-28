/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C0AC.c
 * Original SHA-256: 6797bcaa632b592bbc33537b70823f2807a8c18060f370578ba77f27e2b30d5d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct ResourceTable0800C0AC {
    u8 unknown_00;
    u8 kind;
};

extern void func_0800ACA8(const struct ResourceTable0800C0AC *table, s16 index,
                        u16 *first, u16 *second, u16 *third, u16 *fourth);
extern void func_0800ADD8(const struct ResourceTable0800C0AC *table, u16 index,
                        u32 *offset, u16 *first, u16 *second,
                        u16 *third, u16 *fourth);

static inline void frame_displacement(const struct ResourceTable0800C0AC *table,
                                      u16 *x, u16 *y)
{
    u16 entry;
    u16 current_x, current_y;
    u16 origin_x, origin_y;

    func_0800ACA8(table, -1, &entry, 0, &current_x, &current_y);
    func_0800ADD8(table, entry & 0x3FFF, 0, 0, 0, &origin_x, &origin_y);
    *x = current_x - origin_x;
    *y = current_y - origin_y;
}

/* Target: 0x0800C0AC..0x0800C148, 156 bytes / 74 instructions. */
void func_0800C0AC(const struct ResourceTable0800C0AC *table, u16 *x, u16 *y)
{
    u16 displacement_x, displacement_y;

    if (table->kind == 1) {
        *x = 0;
        *y = 0;
    } else {
        frame_displacement(table, &displacement_x, &displacement_y);
        *x = displacement_x;
        *y = displacement_y;
    }
}
