typedef unsigned char u8;
typedef unsigned short u16;
extern u16 CopyEncodedText(u8 *output,const u8 *source) asm("RetailCall_08018C24");
/* Each copy terminates its own segment. Advance by its actual LOW16 byte count
 * before the next copy; encoded token pairs remain the helper's responsibility.
 * The fourth result is ignored, as in the original void-return frame. */
void AppendFourEncodedTextSegments(u8*,const u8*,const u8*,const u8*,const u8*) asm("CoreRegion_00038D40");
void AppendFourEncodedTextSegments(u8 *output,const u8 *first,const u8 *second,const u8 *third,const u8 *fourth)
{
    output+=CopyEncodedText(output,first);
    output+=CopyEncodedText(output,second);
    output+=CopyEncodedText(output,third);
    CopyEncodedText(output,fourth);
}
__asm__(".global RetailCall_08018C24\n.thumb_set RetailCall_08018C24,0x08018c25");
