/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08137774.c
 * Original SHA-256: d94c30493deb040e04ecca3af506ad5500c405677b9bf37a774f8cf9669d51d3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *effect;
    u8 active;
} PaletteTransition;

void func_08137774(PaletteTransition *state)
{
    state->effect = 0;
    state->active = 0;
}
