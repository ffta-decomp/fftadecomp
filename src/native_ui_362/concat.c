typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 CopyEncodedText(u8 *, const u8 *);
void ConcatenateFiveEncodedText(u8 *, const u8 *, const u8 *, const u8 *, const u8 *, const u8 *) asm("CoreRegion_00038D80");
void ConcatenateFiveEncodedText(u8 *out, const u8 *a, const u8 *b, const u8 *c, const u8 *d, const u8 *e)
{
    out += (u16)CopyEncodedText(out, a);
    out += (u16)CopyEncodedText(out, b);
    out += (u16)CopyEncodedText(out, c);
    out += (u16)CopyEncodedText(out, d);
    CopyEncodedText(out, e);
}
asm(".thumb_set CopyEncodedText,0x08018c25\n");
