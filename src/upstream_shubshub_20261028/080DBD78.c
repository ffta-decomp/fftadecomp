/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DBD78.c
 * Original SHA-256: eefa54d513be1583114df601264be288bb5fa73deae89b25c1db19d75ff7568d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_0801C9F0(s16 x, s16 y, s16 z,
                         s16 *tile_x, s16 *tile_y, s16 *tile_z);

/* Complete [0x080DBD78, 0x080DBDA0): 40 bytes, 19 instructions. */
void func_080DBD78(const Struct080DBD5C *source,
                   s16 *tile_x, s16 *tile_y, s16 *tile_z)
{
    func_0801C9F0(source->x, source->y, source->z, tile_x, tile_y, tile_z);
}
