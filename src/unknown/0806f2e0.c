typedef unsigned short u16;
typedef unsigned int u32;
void InitializeNativeShopChoiceTemplate(u16 *) __asm__("SceneTaskDependency_0006F2E0");
void InitializeNativeShopChoiceTemplate(u16 *tilemap)
{
    const u16 *source = (const u16 *)0x083AF6CC;
    u16 source_index = 0;
    u32 row = 0;
    u16 *destination = tilemap + 3;
    do {
        register u32 shifted_offset __asm__("r0") = row * 14;
        register u32 row_offset __asm__("r4");
        u16 column;
        shifted_offset <<= 16;
        /* The actual wrapping shift result is consumed before normalization. */
        __asm__("" : "+r" (shifted_offset));
        row_offset = shifted_offset >> 16;
        /* Native retains the initialized normalized inner-loop offset in R4. */
        __asm__("" : "+r" (row_offset));
        column = 0;
        row++;
        do {
            if (column < 11) {
                *(u16 *)((u32)destination + ((u32)(column + row_offset) << 1)) = source[source_index] + 192;
                source_index++;
            } else {
                *(u16 *)((u32)destination + ((u32)(column + row_offset) << 1)) = 0;
            }
            column++;
        } while (column < 14);
        row = (u16)row;
    } while (row < 3);
}
