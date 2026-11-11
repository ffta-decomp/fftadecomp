#include "ffta/unsigned_types.h"
typedef void (*CopyCallback)(void *, const void *, int);
typedef void (*ClearCallback)(void *, int);
extern void CallCopy(void *, const void *, int, CopyCallback);
extern void CallClear(void *, int, ClearCallback);
extern void Overlay(u8 *, const u8 *);
extern void *NextRequest(void);
extern void QueueCopy32(void *, const void *, void *, u16);
__asm__(".global CallCopy\n.thumb_set CallCopy, 0x08142251\n.global CallClear\n.thumb_set CallClear, 0x0814224D\n.global Overlay\n.thumb_set Overlay, 0x0802BD45\n.global NextRequest\n.thumb_set NextRequest, 0x0802BA09\n.global QueueCopy32\n.thumb_set QueueCopy32, 0x08000ADD");
void CoreFrontier_0002C72C(u8 *scratch, u16 offset, u8 alternate)
{
    u8 *context = *(u8 **)0x0200F440;
    register u8 *overlay_source __asm__("r4") = context + 0x65C;
    register int overlay_offset __asm__("r6") = 1152;
    register CopyCallback *copy_cell __asm__("r9");
    register u8 *base_tile __asm__("r8");
    register u8 *first_base __asm__("r1");
    register CopyCallback *first_cell __asm__("r1");
    register u32 source_offset __asm__("r1");
    register u8 *context_input __asm__("r0");
    register ClearCallback *clear_cell __asm__("r5");
    if (alternate != 0)
        overlay_offset -= 64;
    /* Native bases begin after the selector-dependent offset is established. */
    __asm__("" : "+r"(overlay_source), "+r"(overlay_offset));
    first_cell = (CopyCallback *)0x0836D4BC;
    __asm__("" : "+r"(first_cell));
    copy_cell = first_cell;
    source_offset = 0xA7C;
    __asm__("" : "+r"(source_offset));
    context_input = context;
    __asm__("add %0, %0, %1" : "+l" (source_offset) : "l" (context_input) : "cc");
    first_base = (u8 *)source_offset;
    __asm__("" : "+r"(first_base));
    base_tile = first_base;
    __asm__("" : "+r"(copy_cell));
    CallCopy(scratch, first_base, 32, *copy_cell);
    clear_cell = (ClearCallback *)0x0836D4B8;
    __asm__("" : "+r"(clear_cell));
    CallClear(scratch + 32, 32, ({ ClearCallback actual = *clear_cell; __asm__("" : "+l" (actual)); actual; }));
    {
        register u8 *destination __asm__("r0") = scratch + 16;
        __asm__("" : "+r" (destination));
        overlay_source += overlay_offset;
        Overlay(destination, overlay_source);
    }
    CallCopy(scratch + 64, base_tile, 32, *copy_cell);
    CallClear(scratch + 96, 32, ({ ClearCallback actual = *clear_cell; __asm__("" : "+l" (actual)); actual; }));
    {
        register u8 *destination __asm__("r0") = scratch + 80;
        __asm__("" : "+r" (destination));
        overlay_source += 32;
        __asm__("" : "+r" (overlay_source));
        Overlay(destination, overlay_source);
    }
    QueueCopy32(NextRequest(), scratch, (void *)(0x06009440 + offset), 32);
}
