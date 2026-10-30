/* Contributed by gg; original source and attribution follow. */
asm(".global f_08022854\n.thumb_set f_08022854,0x08022855\n.global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* SceneRegisteredRoot_00061778
   entry 0x08061778, 76 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void f_0814186C();
extern void f_08022854();

void f_target(void)
{
    u32 *g = (u32 *)0x0200F450;

    if (*g != 0) {
        volatile u16 v = 0;
        void *src = (void *)0x0600E000;
        u32 n = 0x01000800;
        f_0814186C((void *)&v, src, n);
        {
            volatile u16 w = 0;
            f_0814186C((void *)&w, (void *)0x06005000, n);
        }
        f_08022854((void *)*g);
        *g = 0;
    }
}
