/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000DAD94
   entry 0x080DAD94, 40 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 f_08005B6C();

u32 f_target(u16 a, u16 b, u8 c, u32 d)
{
    u8 stk[0x1c];

    *(u16 *)(stk + 0x14) = a;
    *(u16 *)(stk + 0x16) = b;
    *(u16 *)(stk + 0x18) = c;
    return f_08005B6C((void *)0x080D9CF5, 0x14, stk, d);
}
