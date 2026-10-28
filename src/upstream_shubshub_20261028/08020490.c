/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020490.c
 * Original SHA-256: 55f91ec9e79e64c195bd9fe417e8fbb466a06c0ebeb06622784fd6737d4c2a35
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
} TransferState;

extern TransferState g_state_02007F40;

/* 08020490..080204B0: 32 bytes. */
u8 func_08020490(void)
{
    return g_state_02007F40.transfer == 0;
}
