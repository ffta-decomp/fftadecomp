typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern void SetDescriptorByte29(void *, u32);
extern void DrawOwnedList(void *, int, int, u32, u32, u32, u32, u32, u32, u32);
extern void DrawBank(const void *, int, int, u32, u32, u32, u32, u32, u32, u32, u32);
extern void DrawActive(const void *, int, int, u32, u32, u32, u32, u32, u32, u32, u32);
extern u32 UnitBit14(const void *);
__asm__(".global SetDescriptorByte29\n.thumb_set SetDescriptorByte29, 0x08021E65\n.global DrawOwnedList\n.thumb_set DrawOwnedList, 0x08021F19\n.global DrawBank\n.thumb_set DrawBank, 0x08001CF1\n.global DrawActive\n.thumb_set DrawActive, 0x08001F35\n.global UnitBit14\n.thumb_set UnitBit14, 0x080C82B9");
void TaskConstructor45_0002C398(u8 *view)
{
    register u32 flags __asm__("r2") = *(u16 *)(view + 16);
    register u32 mask __asm__("r0");
    register u32 list_mode __asm__("r4");
    __asm__("" : : "r"(flags));
    mask = 16;
    __asm__("" : : "r"(mask));
    mask = (mask & flags) << 16;
    __asm__("" : "+r"(mask));
    list_mode = mask >> 16;
    __asm__("" : "+r"(list_mode));
    if (list_mode != 0) {
        u8 *context = *(u8 **)0x0200F440;
        register u8 *reloaded_context __asm__("r0");
        SetDescriptorByte29(*(void **)(context + 928), context[936]);
        reloaded_context = *(u8 **)0x0200F440;
        __asm__("" : : "r"(reloaded_context));
        DrawOwnedList(*(void **)(reloaded_context + 932), *(s16 *)(view + 4) + 44, *(s16 *)(view + 6) + 16, 0, 0, 0, 0, 0, 0, 0);
        DrawActive((void *)0x08391714, *(s16 *)(view + 4) + 28, *(s16 *)(view + 6) + 8, 0, 0, 0, 0, 0, 0, 0, 12);
        DrawActive((void *)0x08391722, *(s16 *)(view + 4) + 20, *(s16 *)(view + 6), 1, 0, 0, 0, 0, 0, 1, 11);
    } else {
        u32 palette = 12;
        u16 x = *(u16 *)(view + 4);
        if ((flags & 66) == 64) {
            register u32 scaled_x __asm__("r0") = (u32)x << 16;
            register u32 wrapped_delta __asm__("r6");
            /* Original halfword wrap is expressed through its actual 32-bit phase. */
            __asm__("" : : "r"(scaled_x));
            wrapped_delta = 0xFFF80000;
            __asm__("" : : "r"(wrapped_delta));
            scaled_x += wrapped_delta;
            x = scaled_x >> 16;
        }
        if (flags & 2)
            palette = 11;
        DrawBank((void *)0x083916D0, (s16)x, *(s16 *)(view + 6) - 16, 0, list_mode, list_mode, list_mode, list_mode, list_mode, list_mode, palette);
        DrawBank((void *)0x083916E4, *(s16 *)(view + 4), *(s16 *)(view + 6), 0, list_mode, list_mode, list_mode, list_mode, list_mode, list_mode, 12);
        if ((u8)UnitBit14(*(void **)(view + 12)) != 0) {
            register const void *asset __asm__("r3") = (void *)0x083916F2;
            register int x_position __asm__("r1");
            __asm__("" : : "r"(asset));
            if (*(u16 *)(view + 16) & 64) {
                register int raw_x __asm__("r0") = *(s16 *)(view + 4);
                __asm__("" : "+r"(raw_x));
                x_position = raw_x - 8;
            } else {
                register int raw_x __asm__("r0") = *(s16 *)(view + 4);
                __asm__("" : "+r"(raw_x));
                x_position = raw_x + 80;
            }
            DrawBank(asset, x_position, *(s16 *)(view + 6), 0, 0, 0, 0, 0, 0, 0, 12);
        }
        {
            register const void *asset __asm__("r6") = (void *)0x083916FA;
            register int x_position __asm__("r4");
            register u32 current_flags __asm__("r1");
            __asm__("" : : "r"(asset));
            x_position = *(s16 *)(view + 4);
            __asm__("" : "+r"(x_position));
            current_flags = *(u16 *)(view + 16);
            __asm__("" : "+r"(current_flags));
            if (!(current_flags & 64))
                x_position += 80;
            DrawBank(asset, x_position, *(s16 *)(view + 6), 1, 0, 0, ({
                register u32 shifted_flags __asm__("r1") = (current_flags << 16) >> 22;
                register u32 one __asm__("r0") = 1;
                /* This actual outgoing argument clears bit0 using the native mask phase. */
                __asm__("" : "+r"(one) : "r"(shifted_flags));
                one & ~shifted_flags;
            }), 0, 0, 0, 11);
        }
    }
}
