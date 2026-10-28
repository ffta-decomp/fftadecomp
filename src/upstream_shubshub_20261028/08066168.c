/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08066168.c
 * Original SHA-256: 89916fa605ecb0823f6ae68505dd22ca215358f177dfa43aa9722d8e2073a80c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_000[0xBAC];
    u32 value;
} State08066168;

extern State08066168 *data_0200F454;

/* Complete target: [0x08066168, 0x0806617C), 20 bytes, 6 instructions. */
void func_08066168(u32 value)
{
    data_0200F454->value = value;
}
