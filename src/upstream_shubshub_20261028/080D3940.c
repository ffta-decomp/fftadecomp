/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D3940.c
 * Original SHA-256: ccaeb8a5530acb09bc692973e37da4428c654d5d5b147982c09cd674faa6a209
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D3940..0x080D3958: 24 bytes. */
typedef struct {
    u32 unknown_00;
    u32 value;
} HandleState;

extern u32 data_020159C0;
extern HandleState *func_08005BFC(u32 handle);

void func_080D3940(u32 value)
{
    HandleState *state = func_08005BFC(data_020159C0);

    state->value = value;
}
