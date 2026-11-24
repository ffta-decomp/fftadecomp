typedef unsigned char u8;

/* The editing buffer fills unused glyph cells with the text-space token. */
int IsNameBufferBlank(const u8 *name)
{
    u8 index;
    for (index = 0; index <= 8; index++) {
        const u8 *token = index * 2 + name;
        if (token[0] != 0x40 || token[1] != 0x73)
            return 0;
    }
    return 1;
}
