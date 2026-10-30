/* Contributed by gg; original source and attribution follow. */
asm(".global f_08022854\n.thumb_set f_08022854,0x08022855\n.global f_08142250\n.thumb_set f_08142250,0x08142251\n");
/* CoreGlobal36_00022E58
   entry 0x08022E58, 56 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void f_08142250();
extern void f_08022854();

void f_target(void)
{
    u32 *p = (u32 *)0x0200F390;
    u32 h = p[0x17];

    if (h != 0) {
        u32 *q = (u32 *)0x0836D4BC;
        f_08142250((void *)0x03003862, (void *)(h + 2), 0x3FE, q[0]);
        f_08022854((void *)p[0x17]);
        p[0x17] = 0;
    }
}
