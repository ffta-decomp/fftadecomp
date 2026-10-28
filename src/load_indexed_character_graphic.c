typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "asset_addresses.h"

#define INDEXED_CHARACTER_GRAPHICS_ARCHIVE ((const u8 *)INDEXED_CHARACTER_GRAPHICS_ARCHIVE_ADDRESS)

extern const u8 *LookupIndexedArchiveRecord(const u8 *archive, u16 entry_index);
extern u32 DecodeCustomLzssGraphics(u8 *destination, const u8 *compressed);

u32 LoadIndexedCharacterGraphic(u8 *destination, u8 entry_index)
{
    const u8 *compressed = LookupIndexedArchiveRecord(
        INDEXED_CHARACTER_GRAPHICS_ARCHIVE, entry_index);
    return DecodeCustomLzssGraphics(destination, compressed);
}
