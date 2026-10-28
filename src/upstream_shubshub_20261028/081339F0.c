/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081339F0.c
 * Original SHA-256: 999e900e074f53e2ad3a912fbf1cc27f0af8773b38bda762d7294f0c0270ed81
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 func_081339A8(u32 record_index, s32 bit_index, u8 second);

static inline u8 bit_is_set(const u8 *flags, s32 index)
{
    s32 byte_index = index >> 3;
    s32 bit_index = index & 7;
    u8 value = flags[byte_index];

    if ((value >> bit_index) & 1)
        return 1;
    return 0;
}

/* Complete [0x081339F0, 0x08133A38): 72 bytes, 35 instructions. */
u8 func_081339F0(const u8 *flags, u32 record_index)
{
    s32 index;

    for (index = 0; index < 44; index++) {
        if (bit_is_set(flags, index)) {
            if (func_081339A8(record_index, index, 0) == 0)
                return 0;
        }
    }
    return 1;
}
