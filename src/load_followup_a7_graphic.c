typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "asset_addresses.h"

#define FOLLOWUP_A7_ARCHIVE ((const u8 *)FOLLOWUP_A7_ARCHIVE_ADDRESS)

extern void DecodeA7IndexedGraphics(const u8 *archive, u8 *destination,
                                    u16 entry_index, u32 decode_mode);

void LoadFollowupA7Graphic(u8 *destination, u8 entry_index)
{
    DecodeA7IndexedGraphics(FOLLOWUP_A7_ARCHIVE, destination,
                            entry_index, 1);
}
