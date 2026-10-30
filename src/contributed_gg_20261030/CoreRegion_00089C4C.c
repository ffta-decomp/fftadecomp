/* Contributed by gg; original source and attribution follow. */
asm(".global f_08003398\n.thumb_set f_08003398,0x08003399\n");
/* CoreRegion_00089C4C
   entry 0x08089C4C, 56 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void f_08003398(void);

void f_target(void)
{
    volatile u8 *flag;
    volatile u16 *status;
    volatile u16 *shadow;
    volatile u16 *irq;
    u16 value;

    flag = (volatile u8 *)0x030027A4;
    *flag = 0xFF;
    status = (volatile u16 *)0x03000EA0;
    value = status[3];
    value = value & 0xFFFB;
    status[3] = value;
    shadow = (volatile u16 *)0x03000E50;
    *shadow = value;
    irq = (volatile u16 *)0x04000200;
    *irq = value;
    f_08003398();
}
