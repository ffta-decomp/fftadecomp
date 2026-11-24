typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
union PositionPair { s16 half[2]; u8 byte[4]; };
extern s8 *GetRecordPointer(void *);
extern u32 QueryPositionBoundary(u32,u32);
__asm__(".global GetRecordPointer\n.thumb_set GetRecordPointer,0x080a880d\n.global QueryPositionBoundary\n.thumb_set QueryPositionBoundary,0x080d8511");
u32 QueryRecordPositionBoundary(void *handle) __asm__("RemainingBand43_000D8CD4");
u32 QueryRecordPositionBoundary(void *handle)
{
    union PositionPair pair;
    register s16 *first __asm__("r4")=&pair.half[0];
    register s16 *second __asm__("r5")=&pair.half[1];
    s8 *record;
    s32 y;
    __asm__("" : "+r"(first), "+r"(second));
    record=GetRecordPointer(handle);
    *first=record[10];
    y=record[11];
    *second=y;
    return (u8)QueryPositionBoundary(pair.byte[0],(u8)y);
}
