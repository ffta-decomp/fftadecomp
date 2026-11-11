typedef unsigned char u8;
typedef unsigned short u16;

extern u8 gSaveData[];

/* Search 24 observed 264-byte unit records for the three-field state gate. */
int HasSelectedPoolUnit(void)
{
    u8 slot;
    for (slot = 0; slot < 24; ++slot) {
        u8 *unit = gSaveData + slot * 264;
        if (unit[0x84] != 0 && unit[0x170] == 0 &&
            (*(u16 *)(unit + 0xa8) & 8) != 0)
            return 1;
    }
    return 0;
}
