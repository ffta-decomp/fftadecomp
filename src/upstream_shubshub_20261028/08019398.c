/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019398.c
 * Original SHA-256: ce214ed9a597cb1295b27dc280aec43c7b4d5e2f5029b685902276272d0d749f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_0200216A[][2];
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x08019398, 0x080193CC): 52 bytes, 22 instructions. */
u32 func_08019398(u8 *destination, u8 index)
{
    u8 *cursor = destination;
    u8 *entry = data_0200216A[index];

    if (entry[0] < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, entry[0]);

    return 0;
}
