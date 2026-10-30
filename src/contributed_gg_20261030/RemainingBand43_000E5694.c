/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000E5694
   entry 0x080E5694, 28 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 f_08005B6C(void *fn, u32 n, void *buf, u32 a);

u32 f_target(u32 a)
{
    u8 buf[0x1c];
    return f_08005B6C((void *)0x080E5311, 0x2c, buf, a);
}
