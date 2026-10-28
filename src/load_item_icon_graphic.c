typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "asset_addresses.h"

#define ITEM_ICON_ARCHIVE ((const u8 *)ITEM_ICON_ARCHIVE_ADDRESS)

extern void DecodeA7IndexedGraphics(const u8 *archive, u8 *destination,
                                    u16 entry_index, u32 decode_mode);

void LoadItemIconGraphic(u8 *destination, u16 entry_index)
{
    DecodeA7IndexedGraphics(ITEM_ICON_ARCHIVE, destination,
                            entry_index, 1);
}
