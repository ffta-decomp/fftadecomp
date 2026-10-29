typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

#if defined(BUFFER_TAGGED_COPY)
/* OR the tag into each nonzero ASCII code unit; leave the terminator plain. */
void CopyAsciiToTaggedUtf16(u16 *destination, const u8 *source, u32 tag)
{
    u16 *cursor = destination;
    const u8 *input = source;
    u16 character;
    u16 normalized_tag = (u16)tag;

    while (1) {
        character = *input;
        *cursor = character;
        ++input;
        if (character == 0)
            break;
        *cursor = (u16)(*cursor | normalized_tag);
        ++cursor;
    }
}
#elif defined(BUFFER_TAGGED_COPY_EXTRA_NUL)
/* Return the address of a second zero code unit after the string terminator. */
u16 *CopyAsciiToTaggedUtf16WithExtraNul(u16 *destination, const u8 *source, u32 tag)
{
    u16 *cursor = destination;
    const u8 *input = source;
    u16 character;
    u16 normalized_tag = (u16)tag;

    while (1) {
        character = *input;
        *cursor = character;
        ++input;
        if (character == 0)
            break;
        *cursor = (u16)(*cursor | normalized_tag);
        ++cursor;
    }
    ++cursor;
    *cursor = 0;
    return cursor;
}
#elif defined(BUFFER_APPEND_LIMITED)
/* The limit counts copied code units, including a possible terminator. */
u16 *AppendUtf16StringLimited(u16 *destination, const u16 *source, u16 limit)
{
    s16 remaining = (s16)limit;
    u32 character;
    u16 *result = destination;

    while (*destination) {
        ++destination;
    }

    /* Retail decrements a signed 16-bit count before each copy and stops
     * at the -1 sentinel. The zero test uses the copied halfword in bits
     * 16-31 after the destination write. */
    for (;;) {
        --remaining;
        if (remaining == -1)
            break;
        character = *source;
        *destination = character;
        character <<= 16;
        ++source;
        ++destination;
        if (character == 0)
            break;
    }
    return result;
}
#elif defined(BUFFER_COMPARE_LIMITED)
int CompareUtf16StringsLimited(const u16 *left, const u16 *right, u16 limit)
{
    while (limit) {
        u16 left_character = *left++;
        u16 right_character = *right++;
        if (left_character > right_character) return 1;
        if (left_character < right_character) return -1;
        if (left_character == 0) return 0;
        --limit;
    }
    return 0;
}
#elif defined(BUFFER_COPY_PADDED)
/* Copy through the first terminator, then zero-fill the remaining capacity. */
u16 *CopyUtf16StringPadded(u16 *destination, const u16 *source, u16 capacity)
{
    u16 *result = destination;
    while (capacity) {
        u16 character = *source++;
        *destination++ = character;
        --capacity;
        if (character == 0) break;
    }
    while ((s16)capacity > 0) {
        *destination++ = 0;
        --capacity;
    }
    return result;
}
#else
#error Select one UTF-16 buffer helper
#endif
