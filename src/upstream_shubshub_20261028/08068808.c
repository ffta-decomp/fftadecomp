/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08068808.c
 * Original SHA-256: f9041c40ecebe6c4880fe5ffa8ced068eb0ec9915129bf88d79bd7236a409142
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 flags;
} State08068808;

/* Complete [0x08068808, 0x08068810): 8 bytes, 4 instructions. */
u8 func_08068808(const State08068808 *state)
{
    return state->flags & 1;
}
