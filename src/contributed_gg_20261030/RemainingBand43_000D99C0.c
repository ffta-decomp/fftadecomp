/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000D99C0
   entry 0x080D99C0, 84 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 f_08005B6C();

typedef struct {
    u32 f0;
    u32 f4;
    u16 f8;
    u16 fa;
    u16 fc;
    u16 fe;
    u16 f10;
} Inner4;

u32 f_target(u8 a, u32 b, u32 c, u16 d, u16 e, u16 f, u16 g, u16 h, void *ctx)
{
    u8 stk[0x30];
    Inner4 *in = (Inner4 *)(stk + 0x1c);

    in->f0 = b;
    in->f4 = c;
    in->f8 = d;
    in->fa = e;
    in->fc = f;
    in->fe = g;
    in->f10 = h;
    *(u16 *)(stk + 0x14) = a;
    *(u32 *)(stk + 4) = (u32)in;
    return f_08005B6C((void *)0x080D963D, 8, stk, ctx);
}
