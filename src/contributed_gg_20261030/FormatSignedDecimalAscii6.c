/* Contributed by gg; original source and attribution follow. */
asm(".global f_081426B8\n.thumb_set f_081426B8,0x081426B9\n.global f_08142950\n.thumb_set f_08142950,0x08142951\n");
/* FormatSignedDecimalAscii6
   entry 0x08002DE8, 100 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern s32 f_08142950(s32 a, s32 b);
extern s32 f_081426B8(s32 a, s32 b);

void f_target(s16 value, u8 *out)
{
    u8 *p = out;
    s16 v = value;
    u8 sign;
    s32 n;

    if (value < 0) {
        v = -value;
        sign = 0x2D;
    } else {
        sign = 0x20;
    }
    p += 6;
    *p = 0;
    p--;
    n = 6;
    do {
        *p = (u8)(f_08142950(v, 10) + 0x30);
        p--;
        n--;
        v = f_081426B8(v, 10);
    } while (v != 0);
    *p = sign;
    p--;
    n--;
    if (n == 0)
        return;
    do {
        *p = 0x20;
        p--;
        n--;
    } while (n != 0);
}
