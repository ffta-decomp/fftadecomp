typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyCallback)(void *, const void *, int);
extern void CallCopy(void *, const void *, int, CopyCallback);
extern void Overlay(u8 *, const u8 *);
extern u32 Divide(u32, u32);
extern u32 Remainder(u32, u32);
extern void *NextRequest(void);
extern void QueueCopy32(void *, const void *, void *, u16);
__asm__(".global CallCopy\n.thumb_set CallCopy, 0x08142251\n.global Overlay\n.thumb_set Overlay, 0x0802BD45\n.global Divide\n.thumb_set Divide, 0x08142AB1\n.global Remainder\n.thumb_set Remainder, 0x08142B29\n.global NextRequest\n.thumb_set NextRequest, 0x0802BA09\n.global QueueCopy32\n.thumb_set QueueCopy32, 0x08000ADD");
void TaskConstructor45_0002BD90(u8 *scratch, u32 input_number, u32 input_offset)
{
    register u32 number __asm__("r5") = (u16)input_number;
    register u32 saved_number __asm__("r9") = number;
    register u32 offset __asm__("sl") = (u16)input_offset;
    register u8 *incoming __asm__("r0") = scratch;
    register u8 *context __asm__("r4");
    register u8 *glyphs __asm__("r8");
    u8 *output;
    CopyCallback *copy_cell;
    /* True entry snapshots persist while the context bases are constructed. */
    __asm__("" : "+r"(number), "+r"(saved_number), "+r"(offset), "+r"(incoming));
    context = *(u8 **)0x0200F440;
    glyphs = context + 0x65C;
    __asm__("" : : "r"(incoming), "r"(glyphs));
    output = incoming;
    copy_cell = (CopyCallback *)0x0836D4BC;
    CallCopy(output, context + 0x8DC, 32, *copy_cell);
    if (number == 0) {
        CallCopy(output + 32, context + 0xB1C, 32, *copy_cell);
    } else {
        u32 digit_offset = (u16)Divide(number, 10) * 32;
        if (digit_offset != 0)
            Overlay(output, glyphs + digit_offset);
        digit_offset = (u16)Remainder(saved_number, 10) * 32;
        CallCopy(output + 32, glyphs + digit_offset, 32, *copy_cell);
    }
    QueueCopy32(NextRequest(), output, (void *)(0x06013900 + offset), 16);
}
