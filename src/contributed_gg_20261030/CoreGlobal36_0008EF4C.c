/* Contributed by gg; original source and attribution follow. */
asm(".global f_0808B858\n.thumb_set f_0808B858,0x0808B859\n.global f_0808B8E4\n.thumb_set f_0808B8E4,0x0808B8E5\n.global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* CoreGlobal36_0008EF4C
   entry 0x0808EF4C, 68 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void f_0814186C(void *dst, void *src, u32 n);

extern u32 f_0808B8E4(u32 a, u32 b, u32 c, u32 d);
extern void f_0808B858(u32 a, u32 b, u32 c, u32 d);

void f_target(void)
{
    volatile u16 v = 0;
    s32 i;

    f_0814186C((void *)&v, (void *)0x0600E1A0, 0x010007A0);
    for (i = 0; i <= 8; i++) {
        u32 r = f_0808B8E4(6, 1, 0, i * 2);
        f_0808B858(6, r, 0, 0xD);
    }
}
