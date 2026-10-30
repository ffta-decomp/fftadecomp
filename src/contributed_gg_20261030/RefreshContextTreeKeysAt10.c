/* Contributed by gg; original source and attribution follow. */
asm(".global f_0809ABE9\n.thumb_set f_0809ABE9,0x0809ABE9\n.global f_0809AC6D\n.thumb_set f_0809AC6D,0x0809AC6D\n.global f_080C7C48\n.thumb_set f_080C7C48,0x080C7C49\n.global f_080C7CC0\n.thumb_set f_080C7CC0,0x080C7CC1\n");
/* RefreshContextTreeKeysAt10
   entry 0x0809A018, 44 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void f_080C7CC0(u32 a, void *b, void *c);
extern void f_080C7C48(u32 a);
extern void f_0809AC6D(void);
extern void f_0809ABE9(void);

void f_target(u8 *o)
{
    u32 args[2];
    u32 cb = (u32)f_0809AC6D;
    args[0] = *(u32 *)(o + 16);
    args[1] = cb;
    f_080C7CC0(*(u32 *)(o + 16), (void *)f_0809ABE9, args);
    f_080C7C48(*(u32 *)(o + 16));
}
