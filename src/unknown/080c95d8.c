typedef unsigned char u8;
typedef unsigned short u16;

/* This accessor operates on a caller-provided in-memory save image. */
u8 GetGameFlagFromBuffer(u16 flag, const u8 *save)
{
    const u8 *byte = &save[0x1f70 + flag / 8];
    u8 mask = 1 << (flag & 7);

    if (*byte & mask)
        return 1;
    return 0;
}
