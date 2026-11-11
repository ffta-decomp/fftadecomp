typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
extern u8 ReadSaveByte(u16 index);
__asm__(".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9");
/* Preserve the original signed-byte extension, even for low-byte-only callers. */
int ReadSignedSaveByte19(void)
{
    return (s8)ReadSaveByte(19);
}
