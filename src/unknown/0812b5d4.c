typedef unsigned char u8;
typedef unsigned short u16;

/* Text tokens occupy two bytes; a zero high byte terminates this string. */
u16 CountNameTextTokens(const u8 *text)
{
    u16 count = 0;
    for (;;) {
        const u8 *token = count * 2 + text;
        if (token[0] == 0)
            break;
        count++;
    }
    return count;
}
