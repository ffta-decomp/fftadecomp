typedef unsigned char u8;
typedef unsigned short u16;

#if defined(STRING_APPEND_ASCII)
u8 *AppendAsciiString(u8 *destination, const u8 *source)
{
    u8 *result = destination;
    while (*destination) {
        ++destination;
    }
    /* Copy the terminator as part of the string. */
    while ((*destination++ = *source++) != 0) {}
    return result;
}
#elif defined(STRING_APPEND_UTF16)
u16 *AppendUtf16String(u16 *destination, const u16 *source)
{
    u16 *result = destination;
    while (*destination) {
        ++destination;
    }
    /* Copy the terminating code unit as well. */
    while ((*destination++ = *source++) != 0) {}
    return result;
}
#elif defined(STRING_COMPARE_UTF16)
int CompareUtf16Strings(const u16 *left, const u16 *right)
{
    /* Keep both cursors in their incoming registers across loop iterations.
     * The retail loop loads code units into r2/r3 without copying r0 first. */
    register const u16 *left_cursor __asm__("r0") = left;
    register const u16 *right_cursor __asm__("r1") = right;
    for (;;) {
        u16 left_character = *left_cursor;
        u16 right_character = *right_cursor;
        if (left_character > right_character) return 1;
        ++right_cursor;
        if (left_character < right_character) return -1;
        ++left_cursor;
        if (left_character == 0) return 0;
    }
}
#elif defined(STRING_COPY_UTF16)
void CopyUtf16String(u16 *destination, const u16 *source)
{
    while ((*destination++ = *source++) != 0) {}
}
#elif defined(STRING_LENGTH_UTF16)
unsigned int Utf16StringLength(const u16 *text)
{
    u16 length = 0;
    while (*text++) {
        ++length;
    }
    return length;
}
#elif defined(STRING_SWAP_BYTE_PAIRS)
void CopySwappedBytePairs(const u8 *source, u8 *destination, u16 byte_count)
{
    /* Retail counts down from the signed half-length to a 16-bit -1
     * sentinel. Keep the write between the two source advances: source and
     * destination may overlap. */
    signed short pair_index = (signed short)(((signed short)byte_count >> 1) - 1);
    if (pair_index != -1) {
        do {
            u8 first = *source++;
            u8 second = *source;
            *destination = second;
            ++source;
            ++destination;
            *destination++ = first;
            --pair_index;
        } while (pair_index != -1);
    }
}
#else
#error Select one string primitive
#endif
