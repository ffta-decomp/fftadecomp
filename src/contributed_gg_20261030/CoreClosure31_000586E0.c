/* Contributed by gg; original source and attribution follow. */
asm(".global f_0802ACA0\n.thumb_set f_0802ACA0,0x0802ACA1\n.global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* CoreClosure31_000586E0
   entry 0x080586E0, 60 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void f_0814186C(void *dst, void *src, u32 n);

extern void f_0802ACA0(void *p, u32 a, u32 b, u32 c);

void f_target(u8 *a)
{
    volatile u16 v = 0;

    f_0814186C((void *)&v, a, 0x01000014);
    f_0802ACA0(a, 0xC0, 8, 0xA);
    f_0802ACA0(a + 0x14, 0xCA, 8, 0xA);
}
