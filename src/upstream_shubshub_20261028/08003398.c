/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08003398.c
 * Original SHA-256: edabf3dfa852dbc8fa368c621c6605ccf5c0c9912b9ae77f9a9c3b723ae792a2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* plausible: DISPSTAT at 0x04000004 is hardware; bit 0 changes during VBlank. */
#define DISPSTAT (*(volatile u16 *)0x04000004)

/* 0x08003398..0x080033C8: 48 bytes. Wait for the next VBlank. */
void func_08003398(void)
{
    while (DISPSTAT & 1)
        ;
    while (!(DISPSTAT & 1))
        ;
}
