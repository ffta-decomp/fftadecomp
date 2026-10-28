/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148104.c
 * Original SHA-256: 4793b21cd7013a38965b4a5c7c0539240a5bbebb8ad5b7652ef89a03d3945a4c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08148104..0x0814814A: 70 bytes. */
extern u16 func_08148384(u16 value, u16 first, u16 second, u16 third);

void func_08148104(const u16 *source, u16 *destination, u16 count, u16 adjustment)
{
    u16 index;
    for (index = 0; index < count; index++)
        destination[index] = func_08148384(source[index], adjustment,
                                           adjustment, adjustment);
}
