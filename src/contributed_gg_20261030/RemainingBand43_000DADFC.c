/* Contributed by gg; original source and attribution follow. */
asm(".global f_08005BFC\n.thumb_set f_08005BFC,0x08005BFD\n.global f_0800C614\n.thumb_set f_0800C614,0x0800C615\n.global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* RemainingBand43_000DADFC
   entry 0x080DADFC, 40 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern void f_0814186C(void *dst, void *src, u32 n);

void f_target(u32 a)
{
    u8 *p = (u8 *)f_08005BFC(a);
    u32 t = f_0800C614(*(u32 *)(p + 4));
    volatile u16 v = 0;

    f_0814186C((void *)&v, (void *)t, 0x010000A0);
}
