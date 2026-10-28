typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

u32 CanMoveSelectionThreeRows(u8 *object,u32 key) __asm__("CoreClosure31_000583C8");
u32 CanMoveSelectionThreeRows(u8 *object,u32 key)
{
    key=(u16)key;
    if (key==64) {
        if (*(s16*)(object+26)==0)
            goto unavailable;
    } else {
        if (key!=128)
            goto unavailable;
        if ((int)*(s16*)(object+26)+3 >= *(s16*)(object+24))
            goto unavailable;
    }
    return 1;
unavailable:
    return 0;
}
