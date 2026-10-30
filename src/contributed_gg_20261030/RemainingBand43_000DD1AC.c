/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000DD1AC
   entry 0x080DD1AC, 52 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 f_08005B6C();

typedef struct { u32 f0; u8 f4; u8 f5; u16 f6; u16 f8; } In;

u32 f_target(u32 a, u8 b, u16 c, u8 d, u16 e, u16 f, u32 g)
{
    u8 stk[0x28];
    In *in = (In *)(stk + 0x1c);

    in->f0 = a;
    in->f4 = b;
    in->f6 = c;
    in->f5 = d;
    in->f8 = f;
    *(u16 *)(stk + 0x14) = e;
    *(u32 *)(stk + 4) = (u32)in;
    return f_08005B6C((void *)0x080DCAD5, 0xC, stk, g);
}
