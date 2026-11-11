#include "ffta/unsigned_types.h"
extern u32 CopyEncodedText(u8 *, const u8 *);
void ConcatenateTwoEncodedText(u8 *, const u8 *, const u8 *) asm("CoreRegion_00038CF0");
void ConcatenateTwoEncodedText(u8 *out, const u8 *a, const u8 *b)
{
    out += (u16)CopyEncodedText(out, a);
    CopyEncodedText(out, b);
}
asm(".thumb_set CopyEncodedText,0x08018c25\n");
