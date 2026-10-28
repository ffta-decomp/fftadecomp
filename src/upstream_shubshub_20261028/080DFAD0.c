/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DFAD0.c
 * Original SHA-256: 7862c646ce293c50d4ce19c557c2a84b920c0c28da64f8d95d229d8eaf833fce
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DFAD0..0x080DFAEC: 28 bytes. */
typedef struct {
    u8 unknown_00[6];
    u16 flags;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

int func_080DFAD0(int index)
{
    if (func_08005BFC(index)->flags & 0x8000)
        return 1;
    return 0;
}
