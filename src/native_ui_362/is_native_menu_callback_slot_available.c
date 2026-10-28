typedef unsigned char u8;
typedef unsigned int u32;

extern u32 IsCallbackSlotEmpty(u32 handle);

u32 IsNativeMenuCallbackSlotAvailable(const u8 *object)
{
    if ((u8)IsCallbackSlotEmpty(object[7]) != 0)
        return 1;
    return 0;
}

asm(".thumb_set IsCallbackSlotEmpty, 0x080099A5\n");
