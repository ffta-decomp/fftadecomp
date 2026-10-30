/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000D993C
   entry 0x080D993C, 48 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 f_08005B6C();

u32 f_target(u8 a, u8 b, u8 c, u32 d)
{
    u8 stk[0x1c];

    *(u16 *)(stk + 0x14) = a;
    *(u16 *)(stk + 0x16) = b;
    *(u16 *)(stk + 0x18) = c;
    return f_08005B6C((void *)0x080D9529, 0xC, stk, d);
}
