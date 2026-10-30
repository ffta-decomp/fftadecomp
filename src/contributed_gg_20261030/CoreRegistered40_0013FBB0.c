/* Contributed by gg; original source and attribution follow. */
asm(".global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* CoreRegistered40_0013FBB0
   entry 0x0813FBB0, 36 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern void f_0814186C(void *a, u32 b, u32 c);

void f_target(u32 a, u16 b, u8 c)
{
    u16 v;
    v = (u16)((c << 12) | b);
    f_0814186C(&v, a, 0x01000400);
}
