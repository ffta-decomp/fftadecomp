/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08141BB0.c
 * Original SHA-256: dbb53b8b5eb9ddd2690367bdf5fa572dea371619b109942b3218012209276b95
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08141BB0, 0x08141BDE): 46 bytes, 23 instructions. */
const u8 *func_08141BB0(const u8 *source, const u8 *data, u32 count)
{
    u32 remaining = count - 1;
    if (count != 0) {
        do {
            if (*data++ != *source++)
                return data - 1;
        } while (remaining-- != 0);
    }
    return 0;
}
