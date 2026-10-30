/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000DFA70
   entry 0x080DFA70, 96 bytes, restored from the US retail ROM (AFXE).
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
    u8 f0, f1, f2, f3;
    u16 f4;
    u16 f6;
    u32 f8;
    u32 fc;
} Inner5;

u32 f_target(u32 a, u8 b, u8 c, u8 d, u16 e, u16 f, u32 g, u32 h, u16 i, u16 j, void *ctx)
{
    u8 stk[0x2c];
    Inner5 *in = (Inner5 *)(stk + 0x1c);

    in->f0 = b;
    in->f1 = c;
    in->f2 = d;
    in->f4 = e;
    in->f6 = f;
    in->f8 = g;
    in->fc = h;
    *(u32 *)(stk + 4) = a;
    *(u32 *)(stk + 8) = (u32)in;
    *(u16 *)(stk + 0x14) = i;
    *(u16 *)(stk + 0x16) = j;
    return f_08005B6C((void *)0x080DF31D, 0x64, stk, ctx);
}
