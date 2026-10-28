typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct HeadingPairContext { u16 x, y; u8 before_count[3]; u8 count; u8 before_text[8]; u8 text_context[1112]; u16 heading_x, heading_y; };
extern struct HeadingPairContext *HeadingPairContextCell;
extern u8 HeadingTemporary[];
extern u8 HeadingPaletteDestination[];
extern void (*const HeadingClearCell)(void *, u32);
extern void (*HeadingCopyCell)(void *, const void *, u32);
extern const u8 *ResolveHeadingText_080CB4E0(u32);
extern const u8 *ResolveHeadingPalette_080CBABC(u32);
extern u32 RenderHeadingText_08015110(void *, u32, const u8 *, u32, u32);
extern void ReorderHeadingBlocks_0802EAE0(u8 *, const u8 *);
extern void *NextHeadingRequest_0802DFCC(void);
extern void QueueHeadingDma32_08000ADC(void *, u32, u32, u16);
void CoreFrontier_0002EC24(u8 record_id)
{
    register u8 *temporary asm("r5") = HeadingTemporary;
    register u32 converted_offset asm("r0") = 768;
    register u8 *converted asm("r6");
    const u8 *text;
    void *request;
    const u8 *palette;
    register struct HeadingPairContext **context_cell asm("r8");
    register struct HeadingPairContext **initial_cell asm("r1");
    register struct HeadingPairContext **reload_cell asm("r3");
    register struct HeadingPairContext *context asm("r2");
    void (**copy_cell)(void *, const void *, u32);
    u8 *palette_destination;
    u32 row;
    asm("" : "+r" (converted_offset));
    /* Converted buffer = temporary + 768. This original 2-byte ADD fixes
       operand order; all input pointers/offsets are initialized, R6 is defined.
       The instruction island is 2/164 instruction bytes (1.22%), with cc set. */
    asm("add %0, %1, %2" : "=r" (converted)
        : "r" (temporary), "r" (converted_offset) : "cc");
    HeadingClearCell(temporary, 768);
    text = ResolveHeadingText_080CB4E0(record_id);
    initial_cell = &HeadingPairContextCell;
    asm("" : "+r" (initial_cell));
    context_cell = initial_cell;
    asm("" : : "r" (context_cell));
    RenderHeadingText_08015110((*initial_cell)->text_context,
                              (u32)temporary, text, 0, 1);
    ReorderHeadingBlocks_0802EAE0(converted, temporary);
    request = NextHeadingRequest_0802DFCC();
    QueueHeadingDma32_08000ADC(request, (u32)converted, 0x06015c80, 192);
    copy_cell = &HeadingCopyCell;
    palette_destination = HeadingPaletteDestination;
    asm("" : "+r" (copy_cell), "+r" (palette_destination));
    palette = ResolveHeadingPalette_080CBABC(21);
    (*copy_cell)(palette_destination, palette, 32);
    reload_cell = context_cell;
    asm("" : "+r" (reload_cell));
    context = *reload_cell;
    asm("" : "+r" (context));
    {
        register u32 x_offset asm("r0") = 1128;
        register u16 *x_field asm("r1");
        asm("" : "+r" (x_offset));
        x_field = (u16 *)((u8 *)context + x_offset);
        asm("" : "+r" (x_field));
        /* R0 offset is dead after forming the field address; reuse it for the stored value. */
        x_offset = 0xff98;
        asm("" : "+r" (x_offset));
        *x_field = x_offset;
    }
    if (context->count == 0)
        row = context->y + 2;
    else
        row = (context->count + 1) * 2 + context->y;
    {
        register u32 position asm("r0") = row * 8;
        register u16 *field asm("r1");
        asm("" : : "r" (position));
        field = &context->heading_y;
        asm("" : : "r" (field));
        *field = position;
    }
}
asm(".set HeadingPairContextCell,0x0200f444\n.set HeadingTemporary,0x02005d30\n.set HeadingPaletteDestination,0x03003b80\n.set HeadingClearCell,0x0836d4b8\n.set HeadingCopyCell,0x0836d4bc\n.thumb_set ResolveHeadingText_080CB4E0,0x080cb4e1\n.thumb_set ResolveHeadingPalette_080CBABC,0x080cbabd\n.thumb_set RenderHeadingText_08015110,0x08015111\n.thumb_set ReorderHeadingBlocks_0802EAE0,0x0802eae1\n.thumb_set NextHeadingRequest_0802DFCC,0x0802dfcd\n.thumb_set QueueHeadingDma32_08000ADC,0x08000add\n.thumb_set _call_via_r2,0x0814224d\n.thumb_set _call_via_r3,0x08142251\n");
