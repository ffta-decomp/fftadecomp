typedef unsigned short u16;
typedef unsigned int u32;
extern void FillNativeHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u32 UnsignedDecimalRemainder(u32,u32) asm("RetailCall_08142b28");
extern u32 UnsignedDecimalQuotient(u32,u32) asm("RetailCall_08142ab0");
void FormatNativeDecimalTiles(u16 *,u32,u32,u32) asm("CoreRegion_00035A68");
void FormatNativeDecimalTiles(u16 *output_in,u32 width_in,u32 value_in,u32 tile_base_in)
{
    register u16 *output asm("r5") = output_in;
    register u32 width_snapshot asm("r4") = width_in;
    register u32 value asm("r6") = value_in;
    u16 width, tile_base, zero;
    register u16 *zero_slot asm("r1");
    register u32 glyph_offset asm("r1");
    register u32 remainder asm("r0");
    asm("" : "+r"(output), "+r"(width_snapshot), "+r"(value));
    width = (u16)width_snapshot;
    tile_base = (u16)tile_base_in;
    zero_slot = &zero;
    asm("" : "+r"(zero_slot));
    *zero_slot = 0;
    FillNativeHalfwords(&zero,output,0x01000000 | width);
    output += width;
    output--;
    while (width) {
        remainder = UnsignedDecimalRemainder(value,10);
        glyph_offset = tile_base + 30;
        asm("" : "+r"(glyph_offset), "+r"(remainder));
        remainder += glyph_offset;
        *output = remainder;
        output--;
        width--;
        value = UnsignedDecimalQuotient(value,10);
        if (!value) break;
    }
    if (width) {
        do {
            *output = tile_base;
            output--;
            width--;
        } while (width);
    }
}
__asm__(".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_08142b28\n.thumb_set RetailCall_08142b28,0x08142b29\n"
        ".global RetailCall_08142ab0\n.thumb_set RetailCall_08142ab0,0x08142ab1\n");
