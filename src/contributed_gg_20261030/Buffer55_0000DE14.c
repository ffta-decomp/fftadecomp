/* Contributed by gg; original source and attribution follow. */
asm(".global f_0800C804\n.thumb_set f_0800C804,0x0800C805\n");
/* Buffer55_0000DE14
   entry 0x0800DE14, 12 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void f_0800C804(u32 a, u32 b, u32 c);

void f_target(u32 a, u32 b)
{
    f_0800C804(a, b, 2);
}
