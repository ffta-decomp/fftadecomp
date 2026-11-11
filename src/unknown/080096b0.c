typedef unsigned char u8;
typedef unsigned int u32;

/* This is equality status, not a lexical memcmp result. */
int CompareSavedSettingsBytes(const u8 *first, const u8 *second, int length)
{
    if (length <= 0)
        return -1;
    do {
        u32 first_byte = *first;
        u32 second_byte = *second;
        ++second;
        ++first;
        if (first_byte != second_byte)
            return 1;
    } while (--length > 0);
    return 0;
}
