/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812F690.c
 * Original SHA-256: 1aa8d346a9798fd6fbd9483efbba4c054ab62a20915ddf660811f3a66e1d9814
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Unit Unit;
extern u32 func_080CCD50(u16 identifier, u8 field);
extern s32 func_0812F5E0(const Unit *unit, u16 level, u32 field);

static inline u8 alternate_field(u16 identifier)
{
    if (identifier == 0 || func_080CCD50(identifier, 29))
        return 0;
    return 1;
}

/* Complete [0x0812F690, 0x0812F6DE): 78 bytes, 37 instructions. */
s16 func_0812F690(const Unit *unit, u16 identifier, u16 level, s16 value)
{
    if (alternate_field(identifier) != 0)
        value += func_0812F5E0(unit, level, 12);
    else
        value += func_0812F5E0(unit, level, 10);
    return value;
}
