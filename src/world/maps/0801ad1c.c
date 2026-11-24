typedef unsigned char u8;
typedef unsigned int u32;

u8 *SelectMapArrangementBuffer(u32 bank)
{
    /* The retail selector tests the low byte, including for wider callers. */
    u8 selected_bank = (u8)bank;
    u8 *buffer = (u8 *)0x020091a0;
    if (selected_bank != 0)
        buffer += 0x2000;
    return buffer;
}

u8 *SelectMapClippingBuffer(u32 bank)
{
    u8 selected_bank = (u8)bank;
    u8 *buffer = (u8 *)0x0200d1a0;
    if (selected_bank != 0)
        buffer += 0x1000;
    return buffer;
}
