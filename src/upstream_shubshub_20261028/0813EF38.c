/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EF38.c
 * Original SHA-256: 0c1bd61fdac596d4207672be7a62b2cc2c805edb8f4cacb574383e970f276f38
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813EF38..0x0813EF4C: 20 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 position[4];
} PositionState;

extern void func_0814186C(const void *, void *, u32);

void func_0813EF38(PositionState *state, const u16 *position)
{
    func_0814186C(position, state->position, 4);
}
