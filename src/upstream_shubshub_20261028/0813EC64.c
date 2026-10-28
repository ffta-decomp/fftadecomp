/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EC64.c
 * Original SHA-256: 259bdf2c8ce0902fcd55efe674dfcf2fabe3d9737505499c13078991de4c7cdc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813EC64..0x0813EC72: 14 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u16 values[4];
} ValueState;

extern void func_0814186C(const void *, void *, u32);

void func_0813EC64(const ValueState *state, u16 *values)
{
    func_0814186C(state->values, values, 4);
}
