/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD650.c
 * Original SHA-256: 369648da2f04bb6854c7ae6924d366234662d7c1c23b2f4ea2dad0a02cc11308
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} State080DD650;

extern u8 func_0809D8B4(void *object);

/* 0x080DD650 - 32 bytes.
 * Target: 00b54068002808d0c0f72cf9011c0906090e48420843c00f00e0002002bc0847
 */
u8 func_080DD650(const State080DD650 *state)
{
    if (state->object == 0)
        return 0;
    return func_0809D8B4(state->object) != 0;
}
