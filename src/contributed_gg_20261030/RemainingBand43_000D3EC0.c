/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000D3EC0
   entry 0x080D3EC0, 40 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 f_08005B6C();

u32 f_target(u32 p, u16 b, void *ctx)
{
    u8 stk[0x1c];

    *(u16 *)(stk + 0x14) = 0;
    *(u16 *)(stk + 0x16) = b;
    *(u32 *)(stk + 4) = p;
    return f_08005B6C((void *)0x080D3CB5, 0x2c, stk, ctx);
}
