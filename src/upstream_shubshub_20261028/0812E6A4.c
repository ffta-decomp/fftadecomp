/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812E6A4.c
 * Original SHA-256: 727cd5ad8ef73bd266c59c5898b019f7514f558c98a4d7de751100db6180de76
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE8];
    u8 flags[6];
} Unit;

extern u8 func_080CD4D4(const void *unit);
extern u8 func_080C8280(const void *unit);
extern u8 func_08133ADC(const u8 *bits, u32 identifier);

/* 0812E6A4..0812E6DE: 58 bytes, 26 instructions. */
u8 func_0812E6A4(const Unit *unit)
{
    u8 identifier = func_080CD4D4(unit);

    if (identifier == 0)
        return 0;
    if (func_080C8280(unit))
        return 0;
    if (!func_08133ADC(unit->flags, identifier))
        return 0;
    return identifier;
}
