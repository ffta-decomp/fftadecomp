/* Contributed by gg; original source and attribution follow. */
asm(".global f_0800A154\n.thumb_set f_0800A154,0x0800A155\n.global g_02000000\n.set g_02000000,0x02000000\n");
/* CoreFrontier_0000A10C
   entry 0x0800A10C, 72 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 f_0800A154();
extern u8 g_02000000[];

u32 f_target(u8 *o)
{
    u32 r = 0;
    u32 base = 0x08A1A908;
    u32 sum = base + *(u16 *)(base + o[0] * 2);

    sum += *(u16 *)(sum + o[1] * 2);
    *(u32 *)(o + 4) = sum;
    *(u16 *)(o + 2) = 0;

    if ((u8)f_0800A154(o) == 1)
        r = g_02000000[0x219C];

    return r;
}
