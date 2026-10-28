typedef unsigned char u8;

extern u8 gUnitPoolA[];

/* Return the first of twelve 264-byte records whose observed +4 byte is zero. */
u8 *FindEmptyUnitPoolASlot(void)
{
    u8 *record = gUnitPoolA;
    int index;
    for (index = 0; index < 12; ++index, record += 0x108) {
        if (record[4] == 0)
            return record;
    }
    return 0;
}
