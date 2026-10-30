/* Contributed by gg; original source and attribution follow. */
asm(".global f_08003398\n.thumb_set f_08003398,0x08003399\n");
/* CoreDependency29_000231C0
   entry 0x080231C0, 24 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void f_08003398(void);

void f_target(void)
{
    volatile u8 *p = (volatile u8 *)0x03000ED0;
    p[0] = 0xA3;
    p[1] = 0x5D;
    for (;;)
        f_08003398();
}
