typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "asset_addresses.h"

#define INTERLEAVED_A7_ARCHIVE ((const u8 *)INTERLEAVED_A7_ARCHIVE_ADDRESS)

extern void DecodeA7IndexedGraphics(const u8 *archive, u8 *destination,
                                    u16 entry_index, u32 decode_mode);

/* Resolve the observed graphics-ID bands before loading the A7 entry. */
void LoadInterleavedA7Graphic(u8 *destination, u32 raw_graphics_id)
{
    u32 graphics_id = (u8)raw_graphics_id;

    if (graphics_id == 77 || graphics_id > 82)
        graphics_id = 45;
    else if (graphics_id > 43)
        graphics_id = 44;

    DecodeA7IndexedGraphics(INTERLEAVED_A7_ARCHIVE, destination,
                            (u16)(graphics_id - 2), 1);
}
