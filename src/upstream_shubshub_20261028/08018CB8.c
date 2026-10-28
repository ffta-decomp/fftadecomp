/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018CB8.c
 * Original SHA-256: fd94c6c3b90abc992b3b051a015d4ae715042b0d6f28ac67b08558907c193797
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08018CB8, 0x08018CEC): 52 bytes, 26 instructions. */
u16 func_08018CB8(u8 *destination, s8 width)
{
    if (width == 0)
        return 0;

    destination[0] = '@';
    if (width < 0) {
        destination[1] = '<';
    } else {
        destination[1] = '>';
    }
    destination[2] = width < 0 ? -width : width;
    return 3;
}
