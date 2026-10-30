/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000DF7F8
   entry 0x080DF7F8, 52 bytes, restored from the US retail ROM (AFXE).
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
    u8 f4, f5, f6, f7;
    u16 f8;
} Inner3;

u32 f_target(u32 a, u8 b, u8 c, u8 d, u16 e, u16 f, void *ctx)
{
    u8 stk[0x28];
    Inner3 *in = (Inner3 *)(stk + 0x1c);

    in->f0 = a;
    in->f4 = b;
    in->f5 = c;
    in->f6 = d;
    in->f8 = e;
    *(u16 *)(stk + 0x14) = f;
    *(u32 *)(stk + 4) = (u32)in;
    return f_08005B6C((void *)0x080DEC85, 0x18, stk, ctx);
}
