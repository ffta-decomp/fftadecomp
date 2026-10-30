/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000DC1E8
   entry 0x080DC1E8, 60 bytes, restored from the US retail ROM (AFXE).
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
    u32 f8;
    u32 fC;
    u32 f10;
} Inner;

u32 f_target(u32 a, u8 b, u8 c, u8 d, u32 e, u32 f, void *ctx)
{
    u8 stk[0x30];
    Inner *in = (Inner *)(stk + 0x1c);

    in->f0 = a;
    in->f4 = b;
    in->f5 = c;
    in->f6 = d;
    in->fC = e;
    in->f10 = f;
    in->f7 = 0;
    *(u32 *)(stk + 4) = (u32)in;
    return f_08005B6C((void *)0x080DB00D, 0x1118, stk, ctx);
}
