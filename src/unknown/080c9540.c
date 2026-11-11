typedef unsigned char u8;
typedef unsigned short u16;

/* Bit-addressable progression flags stored in the game-state save block. */
extern u8 gGameFlags[];

u8 GetGameFlag(u16 flag)
{
    u8 *byte = &gGameFlags[flag / 8];
    u8 mask = 1 << (flag & 7);

    if (*byte & mask)
        return 1;
    return 0;
}
