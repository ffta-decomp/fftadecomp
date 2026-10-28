/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080205C8.c
 * Original SHA-256: 99e14b0969f2ced5b7114115dc59411725f3004feea569007bec47ccd799fe2a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080205C8, 0x080205F6), 46 bytes. */
extern u8 func_0801FEB8(const u32 *table, const u32 *resources, u16 index,
                       void *secondary_destination, void *primary_destination,
                       u16 first, u16 last);

u8 func_080205C8(const u32 *table, const u32 *resources, u16 index,
                void *secondary_destination, void *primary_destination)
{
    return func_0801FEB8(table, resources, index, secondary_destination,
                         primary_destination, 0,
                         (u16)(((*table - 4) >> 2) - 1));
}
