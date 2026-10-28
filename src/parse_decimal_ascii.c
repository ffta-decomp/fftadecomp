typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

/* Parse a signed decimal number using the game's 16-bit accumulator. */
s32 ParseSignedDecimalAscii(const u8 *text)
{
    s16 negative = 0;
    s16 magnitude = 0;
    u8 digit;

    while (*text == '\t' || *text == ' ') {
        ++text;
    }
    if (*text == '-') {
        negative = 1;
        ++text;
    }
    digit = (u8)(*text - '0');
    if (digit <= 9) {
        /* The accumulator wraps to 16 bits after every decimal digit. */

        do {
            magnitude = (s16)((s16)magnitude * 10 + (*text - '0'));
            ++text;
            digit = (u8)(*text - '0');
        } while (digit <= 9);
    }
    if (negative != 0)
        return (s16)-magnitude;
    return (s16)magnitude;
}
