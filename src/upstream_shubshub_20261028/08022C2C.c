/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022C2C.c
 * Original SHA-256: 4dae49ed11f9d0576168c471ace23c5d0c3dec17de523c8e481b54a048d2deeb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08022C2C..0x08022C44: 24 bytes / 10 instructions. */
struct State08022C2C {
    u8 unknown_00;
    u8 busy;
};

extern struct State08022C2C g_state_0200F390;

u8 func_08022C2C(void)
{
    u8 ready = 0;

    if (g_state_0200F390.busy == 0)
        ready = 1;
    return ready;
}
