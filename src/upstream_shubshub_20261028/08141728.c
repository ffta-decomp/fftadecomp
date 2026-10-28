/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08141728.c
 * Original SHA-256: 5c2382b81ad2bbb8f35ac10a7624a50c7245efc6d4294d2684d857b6c6c6a3aa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_020084D8;
extern void func_081452C0(u16 value);

/* Target: [0x08141728, 0x08141748), 32 bytes, 13 instructions. */
void func_08141728(u16 value)
{
    if (data_020084D8 & 1) {
        func_081452C0(value);
    }
}
