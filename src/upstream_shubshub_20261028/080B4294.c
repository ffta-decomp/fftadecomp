/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080B4294.c
 * Original SHA-256: 71e33003efb1aa623a4e41dae6f78fd1761e4eeaf9aec5666c735ab4ef3caf83
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *unit;
} UnitEntry;

extern s32 func_081304E0(void *unit);
extern s16 func_08130454(void *source, void *destination, s32 total);

/* 0x080B4294..0x080B42D2: 62 bytes. */
s16 func_080B4294(UnitEntry *source, UnitEntry *destination,
                   UnitEntry **entries, s32 count)
{
    s32 total = 0;
    s32 i;

    for (i = 0; i < count; i++)
        total += func_081304E0(entries[i]->unit);
    return func_08130454(source->unit, destination->unit, total);
}
