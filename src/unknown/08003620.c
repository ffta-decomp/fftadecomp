typedef unsigned char u8;
typedef unsigned short u16;

/* Clear the lowest three shadow-control bits, then OR in the supplied byte. */
void MergeDisplayShadowControlByte(u8 value)
{
    volatile u16 *control = (volatile u16 *)0x03000940;
    u16 previous = *control;
    *control = (previous & 0xfff8) | value;
}
