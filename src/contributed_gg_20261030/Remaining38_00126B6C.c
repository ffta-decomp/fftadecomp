/* Contributed by gg; original source and attribution follow. */
asm(".global f_08121B8C\n.thumb_set f_08121B8C,0x08121B8D\n");
/* Remaining38_00126B6C
   entry 0x08126B6C, 48 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void f_08121B8C(void *fn, u32 n, void *stk, u32 z);

void f_target(u8 *p, u8 a, u8 b, u8 c)
{
    u8 stk[0x1c];

    *(u32 *)(stk + 4) = (u32)p;
    *(u16 *)(stk + 0x14) = a;
    *(u16 *)(stk + 0x16) = b;
    *(u16 *)(stk + 0x18) = c;
    f_08121B8C((void *)0x081269E5, 0x34, stk, 0);
}
