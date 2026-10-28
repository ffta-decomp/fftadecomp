/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080205F8.c
 * Original SHA-256: a73a3a9db15b01e6223cfe1353ad96c6a9e82903b19a4f4dd96d6fb3e27a19b5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080205F8..0x08020618: 32 bytes / 13 instructions. */
struct State080205F8 {
    u8 unknown_00[0x184];
    u8 busy;
};

extern struct State080205F8 g_state_02007F40;

u8 func_080205F8(void)
{
    u8 ready = 0;

    if (g_state_02007F40.busy == 0)
        ready = 1;
    return ready;
}
