/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080193CC.c
 * Original SHA-256: 12647408fabcab3716087d3969f6f42ca7d036492c862003ddfd5a56611e02e6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 value;
} NumberState080193CC;

extern NumberState080193CC data_020021B4;
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x080193CC, 0x080193FC): 48 bytes, 19 instructions. */
u32 func_080193CC(u8 *destination)
{
    NumberState080193CC *state = &data_020021B4;
    u8 *cursor = destination;

    if (state->value < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, state->value);
    return 0;
}
