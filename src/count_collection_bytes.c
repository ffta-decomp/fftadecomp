typedef unsigned char u8;

extern const u8 gCollectionByteFlags[];

/* Count occupied bytes in the observed 20-slot collection state. */
u8 CountCollectionBytes(void)
{
    u8 index = 0;
    u8 count = 0;

    while (index < 20) {
        if (gCollectionByteFlags[index] != 0)
            count++;
        index++;
    }
    return count;
}
