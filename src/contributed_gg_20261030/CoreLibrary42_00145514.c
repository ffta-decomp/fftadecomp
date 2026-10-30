/* Contributed by gg; original source and attribution follow. */
asm(".global f_08142248\n.thumb_set f_08142248,0x08142249\n");
/* CoreLibrary42_00145514
   entry 0x08145514, 20 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void f_08142248(u32 a, u32 b);

void f_target(u32 a)
{
    f_08142248(a, *(u32 *)0x02008EE8);
}
