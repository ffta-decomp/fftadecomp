typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 CopyEncodedText(u8 *, const u8 *);
void ConcatenateThreeEncodedText(u8 *, const u8 *, const u8 *, const u8 *) asm("CoreRegion_00038D10");
void ConcatenateThreeEncodedText(u8 *out, const u8 *a, const u8 *b, const u8 *c)
{
    out += (u16)CopyEncodedText(out, a);
    out += (u16)CopyEncodedText(out, b);
    CopyEncodedText(out, c);
}
asm(".thumb_set CopyEncodedText,0x08018c25\n");
