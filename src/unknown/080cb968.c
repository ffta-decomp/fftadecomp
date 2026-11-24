typedef unsigned char u8;
typedef unsigned short u16;
#include "asset_addresses.h"

#define GRAPHICS_LAYOUT_ARCHIVE ((const u8 *)GRAPHICS_LAYOUT_ARCHIVE_ADDRESS)

extern const u8 *LookupIndexedArchiveRecord(const u8 *archive, u16 entry_index);

const u8 *GetIndexedGraphicsLayoutRecord(u8 entry_index)
{
    return LookupIndexedArchiveRecord(GRAPHICS_LAYOUT_ARCHIVE, entry_index);
}
