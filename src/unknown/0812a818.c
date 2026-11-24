typedef unsigned char u8;
typedef unsigned short u16;

extern u16 CountNameTextTokens(const u8 *text);

/* Compare the visible name, then require unused editor cells to be spaces. */
int IsSamePaddedName(const u8 *edited, const u8 *reference)
{
    u16 count = CountNameTextTokens(reference);
    u16 index = 0;
    while (index < count) {
        const u8 *left = index * 2 + edited;
        const u8 *right = index * 2 + reference;
        if (left[0] != right[0] || left[1] != right[1])
            return 0;
        index++;
    }
    while (index <= 8) {
        const u8 *token = index * 2 + edited;
        if (token[0] != 0x40 || token[1] != 0x73)
            return 0;
        index++;
    }
    return 1;
}
