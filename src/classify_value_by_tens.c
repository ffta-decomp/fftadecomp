typedef unsigned char u8;
typedef unsigned short u16;

/* Return the observed three-way range class for an unsigned 16-bit value. */
u8 ClassifyValueByTens(u16 value)
{
    if (value < 10)
        return 0;
    if (value < 20)
        return 1;
    return 2;
}
