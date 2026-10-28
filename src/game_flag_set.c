typedef unsigned char u8;
typedef unsigned short u16;

/* Bit-addressable progression flags stored in the game-state save block. */
extern u8 gGameFlags[];

void SetGameFlag(u16 flag, u16 value)
{
    u8 *byte = &gGameFlags[flag / 8];
    u8 mask = 1 << (flag & 7);

    *byte &= ~mask;
    if (value != 0)
        *byte |= mask;
}
