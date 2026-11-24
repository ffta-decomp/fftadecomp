/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080891BC.c
 * Original SHA-256: 6785698c41013f481c354828e950108871e5d18700396da12c59d45da8744319
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x103];
} Record080891BC;

extern u8 g_state_02000000[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_0814186C(const void *source, void *destination, u32 control);

static inline Record080891BC *record_at(u8 *state, s32 index)
{
    return (Record080891BC *)(state + index * sizeof(Record080891BC) + 0x80);
}

static inline void fill_halfwords(u16 value, void *destination, u32 bytes)
{
    func_0814186C(&value, destination, (bytes >> 1) | 0x01000000);
}

/* Complete target [0x080891BC, 0x08089246): 138 bytes, 63 instructions. */
void func_080891BC(void)
{
    s32 active = 0;
    Record080891BC *record;
    s32 index;
    s32 empty;

    for (index = 1; index < 24; index++) {
        if (g_state_02000000[0x84 + index * sizeof(*record)])
            active++;
    }
    active++;
    if (active == 24)
        return;
    do {
        empty = 0;
        for (index = 1; index < 24; index++) {
            record = record_at(g_state_02000000, index);
            if (record->active) {
                if (empty == 0)
                    continue;
                func_081443FC(record_at(g_state_02000000, empty), record, sizeof(*record));
                fill_halfwords(0, record, sizeof(*record));
            } else if (empty != 0) {
                continue;
            }
            empty = index;
        }
    } while (active != empty);
}
