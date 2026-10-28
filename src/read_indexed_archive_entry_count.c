typedef unsigned char u8;
typedef unsigned short u16;

u16 GetIndexedArchiveEntryCount(const u8 *archive)
{
    return *(const u16 *)(archive + 2);
}
