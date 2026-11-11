/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08137B50.c
 * Original SHA-256: e99cf519fbcf876dc27a8515b7c4560e851474793941c744abfde704fb97547a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[8];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u8 buffer[1];
} ResourceState;

typedef struct {
    u16 *large_tiles;
    u16 *small_tiles;
    void *regions[12];
} TileStorage;

typedef struct {
    u16 mode;
    void *buffer;
} DisplayBuffer;

extern TileStorage data_03002740;
extern ResourceState *data_030027D8;
extern DisplayBuffer data_03000E30;
extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width, u32 height,
    u32 source_x, u32 source_y, u32 source_width, u32 source_height,
    u32 stride, u32 rows);

/* Complete target [0x08137B50, 0x08137C48): 248 bytes. */
u32 func_08137B50(void)
{
    s32 i;
    ResourceState *resource;
    TileStorage *storage = &data_03002740;
    ResourceState **resource_slot = &data_030027D8;
    void *empty = 0;
    void **region = storage->regions;

    for (i = 11; i >= 0; i--)
        *region++ = empty;
    storage->large_tiles = (u16 *)0x06006800;
    storage->small_tiles = (u16 *)0x06005800;
    resource = *resource_slot;
    resource->large_first = (u16 *)0x06006800;
    resource->large_second = (u16 *)0x06006000;
    resource->small_first = (u16 *)0x06005800;
    resource->small_second = (u16 *)0x06005000;
    storage->regions[0] = resource->buffer;
    storage->regions[1] = (u8 *)resource + 0x184;
    storage->regions[2] = (u8 *)resource + 0x334;
    storage->regions[3] = (u8 *)resource + 0x60C;
    storage->regions[4] = storage->regions[2];
    storage->regions[5] = storage->regions[3];
    func_0808A268(0, 3, resource->large_first, resource->large_second,
        (u16 *)0x06006800, (u16 *)0x06006000,
        0, 0, 0, 0, 32, 32, 0, 0, 32, 32, 32, 32);
    func_0808A268(1, 12, (*resource_slot)->small_first,
        (*resource_slot)->small_second, (u16 *)0x06005800, (u16 *)0x06005000,
        0, 0, 0, 0, 32, 32, 0, 0, 32, 32, 32, 32);
    data_03000E30.mode = 4;
    data_03000E30.buffer = (u8 *)*resource_slot + 0x2270;
    return 0;
}
