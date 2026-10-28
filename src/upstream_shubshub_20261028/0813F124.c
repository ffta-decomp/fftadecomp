/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813F124.c
 * Original SHA-256: d92ebaa1df83fb3fbc21a4f0f0aa32b2b5545f2e584021958469157c9fa800a3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813F124..0x0813F12C: 8 bytes. */
typedef struct {
    u32 value;
    u8 status;
} ValueState;

void func_0813F124(ValueState *state)
{
    state->value = 0;
    state->status = 0;
}
