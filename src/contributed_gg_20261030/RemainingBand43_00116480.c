/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_00116480
   entry 0x08116480, 72 bytes, restored from the US retail ROM (AFXE).
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
    u16 f0;
    u16 f2;
    u8 f4, f5, f6, f7;
    u16 f8;
    u16 fa;
    u32 fc;
} Inner2;

u32 f_target(u8 a, u16 b, u16 c, u8 d, u8 e, u16 f, u16 g, u32 h, void *ctx)
{
    u8 stk[0x2c];
    Inner2 *in = (Inner2 *)(stk + 0x1c);

    in->f4 = a;
    in->f0 = b;
    in->f2 = c;
    in->f5 = d;
    in->f6 = e;
    in->f8 = f;
    in->fa = g;
    in->fc = h;
    *(u32 *)(stk + 4) = (u32)in;
    return f_08005B6C((void *)0x081160E5, 0x38, stk, ctx);
}
