typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyCallback)(void *, const void *, int);
extern void CallCopy(void *, const void *, int, CopyCallback);
typedef void (*ClearCallback)(void *, int);
extern void CallClear(void *, int, ClearCallback);
extern u32 Divide(u32, u32);
extern u32 Remainder(u32, u32);
extern void *NextRequest(void);
extern void QueueCopy32(void *, const void *, void *, u16);
__asm__(".global CallCopy\n.thumb_set CallCopy, 0x08142251\n.global CallClear\n.thumb_set CallClear, 0x0814224D\n.global Divide\n.thumb_set Divide, 0x08142AB1\n.global Remainder\n.thumb_set Remainder, 0x08142B29\n.global NextRequest\n.thumb_set NextRequest, 0x0802BA09\n.global QueueCopy32\n.thumb_set QueueCopy32, 0x08000ADD");
void TaskConstructor45_0002BC7C(u8 *scratch, u32 input_number, u32 input_offset)
{
    register u32 number __asm__("r4") = (u16)input_number;
    register u32 offset __asm__("r8") = (u16)input_offset;
    register u8 *incoming __asm__("r0") = scratch;
    register u8 *context __asm__("r6");
    u8 *glyphs;
    u8 *output;
    /* Proven sibling family: retain incoming pointer until context bases exist. */
    __asm__("" : "+r"(number), "+r"(offset), "+r"(incoming));
    context = *(u8 **)0x0200F440;
    glyphs = context + 0x65C;
    __asm__("" : : "r"(incoming), "r"(glyphs));
    output = incoming;
    if (number == 0) {
        CallClear(output, 32, *(ClearCallback *)0x0836D4B8);
        {
            register CopyCallback *cell __asm__("r2") = (CopyCallback *)0x0836D4BC;
            register u8 *target __asm__("r0");
            register u32 source_offset __asm__("r3");
            register const u8 *source __asm__("r1");
            register CopyCallback callback __asm__("r3");
            /* Native zero-path cell address precedes target/source construction. */
            __asm__("" : : "r"(cell));
            target = output + 32;
            source_offset = 0xB1C;
            __asm__("" : : "r"(target), "r"(source_offset));
            source = context + source_offset;
            __asm__("" : : "r"(source));
            callback = *cell;
            /* Capture the real callback before its address register becomes an argument. */
            __asm__("" : "+r"(callback));
            CallCopy(target, source, 32, callback);
        }
    } else {
        u32 digit_offset = (u16)Divide(number, 10) * 32;
        if (digit_offset != 0) {
            register CopyCallback *cell __asm__("r0") = (CopyCallback *)0x0836D4BC;
            register const u8 *source __asm__("r1");
            register CopyCallback callback __asm__("r3");
            __asm__("" : : "r"(cell));
            source = glyphs + digit_offset;
            __asm__("" : : "r"(source));
            callback = *cell;
            __asm__("" : "+r"(callback));
            CallCopy(output, source, 32, callback);
        }
        else
            CallClear(output, 32, *(ClearCallback *)0x0836D4B8);
        digit_offset = (u16)Remainder(number, 10) * 32;
        {
            register CopyCallback *cell __asm__("r2") = (CopyCallback *)0x0836D4BC;
            register u8 *target __asm__("r0");
            register const u8 *source __asm__("r1");
            register CopyCallback callback __asm__("r3");
            __asm__("" : : "r"(cell));
            target = output + 32;
            source = glyphs + digit_offset;
            __asm__("" : : "r"(target), "r"(source));
            callback = *cell;
            __asm__("" : "+r"(callback));
            CallCopy(target, source, 32, callback);
        }
    }
    QueueCopy32(NextRequest(), output, (void *)(0x06013900 + offset), 16);
}
