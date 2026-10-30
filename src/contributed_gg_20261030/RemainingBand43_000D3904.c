/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005BFC\n.thumb_set f_08005BFC,0x08005BFD\n");
/* RemainingBand43_000D3904
   entry 0x080D3904, 20 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 f_08005BFC(u32 a);

u32 f_target(void)
{
    return f_08005BFC(*(u32 *)0x020159C0) + 0xC;
}
