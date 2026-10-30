/* Contributed by gg; original source and attribution follow. */
asm(".global f_080C7CC0\n.thumb_set f_080C7CC0,0x080C7CC1\n");
/* CoreGlobal36_00022044
   entry 0x08022044, 36 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void f_080C7CC0(u32 a, void *b, void *c);

u32 f_target(u8 *o)
{
    u8 v = 1;
    f_080C7CC0(*(u32 *)(o + 8), (void *)0x08022195, &v);
    return v;
}
