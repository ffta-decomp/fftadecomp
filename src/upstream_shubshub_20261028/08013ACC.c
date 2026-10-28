/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013ACC.c
 * Original SHA-256: b639706461f70fbce6b38f213ba63e8814af5304fb31b87d887767ba57c9a657
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08013ACC..0x08013B06: 58 bytes. */
u8 func_08013ACC(u8 value, u16 flags)
{
    u16 related = flags & 0x1C20;

    if (flags & 4) {
        return value * 2;
    }
    if (!related) {
        return value * 2 + 3;
    }
    return value * 2 + 2;
}
