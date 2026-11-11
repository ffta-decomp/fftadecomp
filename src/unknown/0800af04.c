/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0800AF04.c
 * Original SHA-256: 426a594c34ac7950834b9ea40d34fc996a7d2e651cc29777072eb472a5171be5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

struct Table0800ACA8 {
    u8 unknown_00;
    u8 status;
    u16 flags;
    s16 timer;
    s16 current;
    u16 unknown_08;
    u16 loop_start;
    u16 end;
    u8 unknown_0E[0xA];
    const u8 *data;
};

extern void func_0800ACA8(struct Table0800ACA8 *table, s16 index,
                        u16 *first, u16 *second, u16 *third, u16 *fourth);

/* Target: [0x0800AF04, 0x0800AF8A), 134 bytes. */
u8 func_0800AF04(struct Table0800ACA8 *table, u16 delay)
{
    u8 updated = 0;
    s16 value;

    if (table->status != 2) {
        table->timer++;
        if (table->timer >= delay) {
            u32 previous = (u16)table->current;

            table->current = previous + 1;
            table->timer = 0;
            updated = 1;
            if (table->current == table->end) {
                func_0800ACA8(table, table->current, 0, (u16 *)&value, 0, 0);
                if (value == 999)
                    table->current = table->loop_start;
            } else if (table->current > table->end) {
                if (table->flags & 0x100) {
                    table->current = table->loop_start;
                } else {
                    table->status = 1;
                    if (table->flags & 0x2000)
                        table->current = previous;
                }
            }
        }
    }
    return updated;
}
