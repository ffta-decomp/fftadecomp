/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080680F8.c
 * Original SHA-256: 1313a4728d9f5358b16a0e22f9389e0d90e9376fca671a19147d079822a73c5a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080680F8..0x0806810E: 22 bytes. */
extern u32 func_080CCA80(void);

u8 func_080680F8(void)
{
    return (u8)func_080CCA80() != 0;
}
