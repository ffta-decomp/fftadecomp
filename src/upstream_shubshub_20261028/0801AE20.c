/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801AE20.c
 * Original SHA-256: c05500c24899fdaf5af1108e5de06d5b7e05b648512771995ac543028764c7c9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State0801AE20 {
    u16 unknown_00[22];
    u16 flags : 16;
};

extern struct State0801AE20 g_state_02007F40;

/* 0x0801AE20..0x0801AE34: 20 bytes. */
void func_0801AE20(void)
{
    g_state_02007F40.flags |= 0x100;
}
