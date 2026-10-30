/* Contributed by gg; original source and attribution follow. */
asm(".global f_081439C8\n.thumb_set f_081439C8,0x081439C9\n");
/* CoreLibrary42_00144314
   entry 0x08144314, 24 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { u32 a, b, c, d; } Args;

extern u32 f_081439C8(Args *args);

u32 f_target(u32 a, u32 b, u32 c, u32 d)
{
    Args g;
    g.a = a;
    g.b = b;
    g.c = c;
    g.d = d;
    return f_081439C8(&g);
}
