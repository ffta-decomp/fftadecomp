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
void TaskConstructor45_0002BEB0(u8 *scratch, u32 input_number, u32 input_first, u32 input_second, u32 input_compact)
{
    u32 number = (u16)input_number;
    register u32 first_offset __asm__("r9") = (u16)input_first;
    register u32 second_offset __asm__("sl") = (u16)input_second;
    u32 compact = (u8)input_compact;
    register u8 *incoming __asm__("r0") = scratch;
    register u8 *context __asm__("r6");
    register u8 *glyphs __asm__("r4");
    register u8 *third_tile __asm__("r8");
    register u8 *output __asm__("r5");
    register u32 third_displacement __asm__("r2");
    /* Retain actual width-limited arguments while constructing context bases. */
    __asm__("" : "+r"(number), "+r"(first_offset), "+r"(second_offset), "+r"(incoming) : "r"(compact));
    context = *(u8 **)0x0200F440;
    glyphs = context + 0x65C;
    __asm__("" : : "r"(incoming), "r"(glyphs));
    output = incoming;
    third_displacement = 64;
    __asm__("" : : "r"(third_displacement));
    third_tile = output + third_displacement;
    __asm__("" : : "r"(third_tile));
    if (number == 0) {
        ClearCallback *clear_cell = (ClearCallback *)0x0836D4B8;
        CallClear(incoming, 64, *clear_cell);
        {
            register CopyCallback *cell __asm__("r0") = (CopyCallback *)0x0836D4BC;
            register u32 source_offset __asm__("r2");
            register const u8 *source __asm__("r1");
            register CopyCallback callback __asm__("r3");
            __asm__("" : : "r"(cell));
            source_offset = 0xB1C;
            __asm__("" : : "r"(source_offset));
            source = context + source_offset;
            __asm__("" : : "r"(source));
            callback = *cell;
            __asm__("" : "+r"(callback));
            CallCopy(third_tile, source, 32, callback);
        }
        CallClear(output + 96, 32, *clear_cell);
    } else {
        u32 digit_offset = (u16)Divide(number, 100) * 32;
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
        digit_offset = (u16)Remainder((u16)Divide(number, 10), 10) * 32;
        if (number > 99 || digit_offset != 0) {
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
        } else {
            register ClearCallback *cell __asm__("r1") = (ClearCallback *)0x0836D4B8;
            register u8 *target __asm__("r0");
            register ClearCallback callback __asm__("r2");
            __asm__("" : : "r"(cell));
            target = output + 32;
            __asm__("" : : "r"(target));
            callback = *cell;
            __asm__("" : "+r"(callback));
            CallClear(target, 32, callback);
        }
        digit_offset = (u16)Remainder(number, 10) * 32;
        {
            register CopyCallback *cell __asm__("r0") = (CopyCallback *)0x0836D4BC;
            register const u8 *source __asm__("r1");
            register CopyCallback callback __asm__("r3");
            __asm__("" : : "r"(cell));
            source = glyphs + digit_offset;
            __asm__("" : : "r"(source));
            callback = *cell;
            __asm__("" : "+r"(callback));
            CallCopy(third_tile, source, 32, callback);
        }
        {
            register ClearCallback *cell __asm__("r1") = (ClearCallback *)0x0836D4B8;
            register u8 *target __asm__("r0");
            register ClearCallback callback __asm__("r2");
            __asm__("" : : "r"(cell));
            target = third_tile + 32;
            __asm__("" : : "r"(target));
            callback = *cell;
            __asm__("" : "+r"(callback));
            CallClear(target, 32, callback);
        }
    }
    QueueCopy32(NextRequest(), output, (void *)(0x06013900 + first_offset), 16);
    QueueCopy32(NextRequest(), third_tile, (void *)(0x06013900 + second_offset), compact != 0 ? 8 : 16);
}
