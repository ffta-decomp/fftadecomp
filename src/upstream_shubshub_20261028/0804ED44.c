/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804ED44.c
 * Original SHA-256: c5957844528966fcdc024dfffa96be669c482347793f179fbdc7f7bb72b34c51
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TileRegion0804ED44 {
    u8 unknown_00[0x28];
};

struct Menu0804ED44 {
    u8 unknown_00[0x250];
    struct TileRegion0804ED44 region;
};

extern struct Menu0804ED44 *data_0201F54C;
extern u8 func_08017180(struct TileRegion0804ED44 *region);

u8 func_0804ED44(void)
{
    return func_08017180(&data_0201F54C->region);
}
