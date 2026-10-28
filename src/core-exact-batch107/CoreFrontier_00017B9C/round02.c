typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SelectionTileRows {
    u8 unknown_00[21]; u8 width; u8 unknown_16; u8 period;
    s16 total; u16 top; u16 tile_base;
};
extern int SelectionRowSignedModulo(int, int);
u32 GetManagedSelectionTileOffset(struct SelectionTileRows *list, u32 input_row)
{
    s16 sum;
    u32 index;
    u32 row_stride;
    register u32 remainder asm("r0");

    sum = (u16)(list->top + (s8)input_row);
    if (sum < 0)
        index = 0;
    else if (sum > list->total - 1)
        index = (u16)list->total - 1;
    else
        index = (u16)sum;
    index = (u16)index;
    remainder = (u16)SelectionRowSignedModulo(index, list->period);
    /* Native materializes each factor separately before the product. */
    asm("" : "+r" (remainder));
    row_stride = (u32)list->width * 2;
    asm("" : "+r" (row_stride));
    return (u16)(remainder * row_stride + list->tile_base);
}
asm(".thumb_set SelectionRowSignedModulo, 0x08142951\n");
