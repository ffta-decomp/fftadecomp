typedef unsigned char u8;
typedef unsigned short u16;

/* This accessor operates on a caller-provided in-memory save image. */
void SetGameFlagInBuffer(u16 flag, u16 value, u8 *save)
{
    u8 *byte = &save[0x1f70 + flag / 8];
    u8 mask = 1 << (flag & 7);

    *byte &= ~mask;
    if (value != 0)
        *byte |= mask;
}
