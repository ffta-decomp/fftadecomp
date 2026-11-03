typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
struct StreamContext {
    u8 unaccessed0[12];
    u16 mode_flags;
    u8 unaccessed14[22];
    s16 depth;
    u8 unaccessed38[14];
    u16 x;
    u16 y;
    u8 phase;
    u8 unaccessed57;
    u16 flags;
};
extern struct StreamContext *gCurrentStream;
extern const u8 gCursorOffsets[];
extern const u8 gCursorDescriptor[];
extern void SubmitCursor(const void *, u32, s32, u32,
                         u32, u32, u32, u32, s32, u32, u32);
__asm__(".global gCurrentStream\n.set gCurrentStream,0x0200918c\n"
        ".global gCursorOffsets\n.set gCursorOffsets,0x0836d60c\n"
        ".global gCursorDescriptor\n.set gCursorDescriptor,0x0851ba6a\n"
        ".global SubmitCursor\n.thumb_set SubmitCursor,0x08001cf1");
void EmitStreamCursor(void)
{
    struct StreamContext *initial_context = gCurrentStream;
    register struct StreamContext *render_context __asm__("r3");
    u8 *phase;
    u8 old_phase;
    u8 vertical_offset;
    register const u8 *offsets __asm__("r3");
    if (!(initial_context->flags & 1))
        return;
    offsets = gCursorOffsets;
    __asm__("" : "+r"(offsets));
    old_phase = initial_context->phase;
    initial_context->phase = old_phase + 1;
    {
        register u32 table_value __asm__("r0") = (s32)(s8)old_phase;
        /* Real ROM byte read; R0 is the signed index, then address, then byte. */
        __asm__("add %0, %0, %1\n\tldrb %0, [%0]"
                : "+r"(table_value) : "r"(offsets) : "cc", "memory");
        vertical_offset = table_value + 10;
    }
    render_context = gCurrentStream;
    __asm__("" : "+r"(render_context));
    if (render_context->mode_flags & 32) {
        u32 shifted_offset = (u32)vertical_offset << 24;
        __asm__("" : "+r"(shifted_offset));
        shifted_offset += 252u << 24;
        vertical_offset = shifted_offset >> 24;
    }
    {
        register const void *resource __asm__("r0") = gCursorDescriptor;
        register u32 target_x __asm__("r1") = render_context->x;
        s32 target_y;
        u32 outgoing_zero;
        __asm__("" : "+r"(resource), "+r"(target_x));
        target_y = (s8)vertical_offset + render_context->y;
        outgoing_zero = 0;
        __asm__("" : "+r"(outgoing_zero) : "r"(target_y), "r"(resource), "r"(target_x));
        SubmitCursor(resource, target_x, target_y, 0,
                     outgoing_zero, outgoing_zero, outgoing_zero, outgoing_zero,
                     render_context->depth, outgoing_zero, outgoing_zero);
    }
    phase = &gCurrentStream->phase;
    *phase &= 31;
}
