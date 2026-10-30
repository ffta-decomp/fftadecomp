/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000D9B18
   entry 0x080D9B18, 32 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 f_08005B6C(void *fn, u32 n, void *blob, u32 extra);
typedef struct { u8 p0[4]; void *p1; u8 p2[0xC]; u16 w14; u8 tail[6]; } Blob;

u32 f_target(u16 a, void *b, u32 c)
{
    Blob s;
    s.w14 = a;
    s.p1 = b;
    return f_08005B6C((void *)0x080D9BCD, 0x10, &s, c);
}
