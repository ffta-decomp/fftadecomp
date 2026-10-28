typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
u32 CoreFrontier_00017A90(u8 *object,u32 input_direction)
{
    u16 direction=input_direction;
    switch(direction) {
    case 128:
        if (*(s16 *)(object+26)+object[22]>=*(s16 *)(object+24)) return 0;
        break;
    case 64:
        if (*(s16 *)(object+26)==0) return 0;
        break;
    }
    return 1;
}
