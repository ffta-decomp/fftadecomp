/* Contributed by gg; original source and attribution follow. */
asm(".global f_0800543C\n.thumb_set f_0800543C,0x0800543D\n.global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* SceneTaskDependency_0005C520
   entry 0x0805C520, 72 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void f_0800543C(void *a, void *b);
extern void f_0814186C(void *dst, void *src, u32 n);

void f_target(void)
{
    u8 *base = (u8 *)0x02003CB0;
    f_0800543C(base, (void *)0x083AEEA4);
    f_0814186C(base + 0x9A0, (void *)0x0600E180, 0x20);
    f_0800543C(base, (void *)0x083AF8AC);
    f_0814186C(base, (void *)0x06016400, 0x1A0);
}
