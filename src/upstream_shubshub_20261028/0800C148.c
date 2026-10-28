/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C148.c
 * Original SHA-256: df18f2fde2be76ffa5b824e7d631a31bdd4fa65efa64cc24d6f6fbb87b6f0f70
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 kind;
} KindState;

/* 0800C148..0800C15A: 18 bytes, 9 instructions. */
u8 func_0800C148(const KindState *state)
{
    return state->kind == 1;
}
