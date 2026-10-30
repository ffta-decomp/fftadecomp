/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005BFC\n.thumb_set f_08005BFC,0x08005BFD\n");
/* RemainingBand43_000D3A30
   entry 0x080D3A30, 32 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 f_08005BFC(u32 a);

void f_target(void)
{
    u8 *p = (u8 *)f_08005BFC(*(u32 *)0x020159C0);

    *(u16 *)(p + 2) &= 0xFFDF;
}
