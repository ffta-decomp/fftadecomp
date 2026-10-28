typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Call_08017AF4(u8 *, int, u32);
extern void Call_08017FB0(u8 *, u32);
extern void Call_080023D0(u8 *);
extern void Call_08141540(u32);
__asm__(".global Call_08017AF4\n.thumb_set Call_08017AF4,0x08017AF5\n.global Call_08017FB0\n.thumb_set Call_08017FB0,0x08017FB1\n.global Call_080023D0\n.thumb_set Call_080023D0,0x080023D1\n.global Call_08141540\n.thumb_set Call_08141540,0x08141541");
extern u8 InputState[];
__asm__(".global InputState\n.set InputState,0x03000000");
u32 TaskConstructor45_00028708(u8 *input_request, u32 input_keys)
{
    register u8 *request __asm__("r5") = input_request;
    u16 keys = input_keys;
    register u8 *row_control __asm__("r6") = request + 88;
    register int row __asm__("r4") = 0;
    int changed = 0;
    __asm__("" : "+r"(request), "+r"(row_control), "+r"(row));
    if (keys & 128) {
        register u8 *target __asm__("r0") = request + 56;
        __asm__("" : "+r"(target));
        row = *(s8 *)(row_control + 17);
        __asm__("" : "+r"(row), "+r"(target));
        Call_08017AF4(target, row, 255);
        if (*(s8 *)(request + 9) > 1) Call_08141540(109);
        Call_080023D0(InputState);
        row = (u8)(row + 1);
        if ((s8)row >= *(s8 *)(request + 9)) row = 0;
        goto apply;
    } else if (keys & 64) {
        register u8 *target __asm__("r0") = request + 56;
        __asm__("" : "+r"(target));
        row = *(s8 *)(row_control + 17);
        __asm__("" : "+r"(row), "+r"(target));
        Call_08017AF4(target, row, 255);
        if (*(s8 *)(request + 9) > 1) Call_08141540(109);
        Call_080023D0(InputState);
        row = (u8)(row - 1);
        if ((s8)row < 0) {
            register u32 count __asm__("r0") = request[9];
            __asm__("" : "+r"(count));
            row = (u8)(count - 1);
        }
        changed = 1;
    }
    if (changed) {
apply:
        row = (u32)row << 24;
        __asm__("" : "+r"(row));
        Call_08017FB0(row_control, (u32)row >> 24);
        {
            register u8 *target __asm__("r0") = request + 56;
            __asm__("" : "+r"(target), "+r"(row));
            row >>= 24;
            __asm__("" : "+r"(row), "+r"(target));
            Call_08017AF4(target, row, 11);
        }
    }
    return 0;
}
