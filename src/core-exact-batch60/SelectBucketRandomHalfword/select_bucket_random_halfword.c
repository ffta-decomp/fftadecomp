typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

extern u32 UnsignedDivide(u32 dividend, u32 divisor);
extern u32 NextRandom15(void);
extern s32 SignedModulo(s32 dividend, s32 divisor);
extern const u16 gBucketRandomHalfwords[10][20];

/* The source byte selects a capped group of five before the random cell. */
u16 SelectBucketRandomHalfword(u32 source_value)
{
    u8 bucket = (u8)UnsignedDivide((u8)source_value, 5);
    s16 random_value;
    s16 cell_index;
    s32 byte_offset;
    const u16 (*table)[20];

    if (bucket > 9)
        bucket = 9;
    table = gBucketRandomHalfwords;
    random_value = (s16)NextRandom15();
    cell_index = SignedModulo(random_value, 20);
    byte_offset = (s32)cell_index * 2;
    byte_offset += (u32)bucket * 40;
    return *(const u16 *)((const u8 *)table + byte_offset);
}
