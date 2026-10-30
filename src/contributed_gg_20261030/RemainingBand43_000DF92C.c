/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005B6C\n.thumb_set f_08005B6C,0x08005B6D\n");
/* RemainingBand43_000DF92C
   entry 0x080DF92C, 36 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 f_08005B6C(void *fn, u32 n, void *blob);
typedef struct { u8 p0[4]; void *p1; u8 p2[0xC]; u16 w14; u16 w16; u8 tail[4]; } Blob;

u32 f_target(void *a, u8 b, u16 c)
{
    Blob s;
    s.p1 = a;
    s.w14 = c;
    s.w16 = b;
    return f_08005B6C((void *)0x080DE919, 0x10, &s);
}
