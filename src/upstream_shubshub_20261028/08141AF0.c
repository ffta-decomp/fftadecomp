/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08141AF0.c
 * Original SHA-256: 4408122b24a59db8de3eb71811a0a6a7aeb7cf50b1031caf57f96c86935ea2a3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08141AF0, 0x08141B12): 34 bytes, 17 instructions. */
void func_08141AF0(const u8 *source, u8 *destination, u32 count)
{
    u32 remaining = count - 1;
    if (count != 0) {
        do {
            *destination++ = *source++;
        } while (remaining-- != 0);
    }
}
