/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808B4FC.c
 * Original SHA-256: 58552e3d6a04e013a8be6d7509a3ef706392e192a18d33bca1faac7d723c0893
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
} ResourceContext;

typedef struct {
    u16 *large_tiles;
    u16 *small_tiles;
} TileStorage;

extern ResourceContext *data_03002818;
extern TileStorage data_03002740;

extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width, u32 height,
    u32 source_x, u32 source_y, u32 source_width, u32 source_height,
    u32 stride, u32 rows);

void func_0808B4FC(void)
{
    func_0808A268(0, 3, data_03002818->large_first,
        data_03002818->large_second, data_03002740.large_tiles,
        data_03002740.large_tiles + 0x1000, 0, 0, 0, 0, 32, 64,
        0, 0, 32, 64, 32, 64);
    func_0808A268(1, 12, data_03002818->small_first,
        data_03002818->small_second, data_03002740.small_tiles,
        data_03002740.small_tiles + 0x400, 0, 0, 0, 0, 32, 32,
        0, 0, 32, 32, 32, 32);
}
