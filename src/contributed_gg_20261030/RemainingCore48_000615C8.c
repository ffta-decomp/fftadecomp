/* Contributed by gg; original source and attribution follow. */
asm(".global f_08013404\n.thumb_set f_08013404,0x08013405\n");
/* RemainingCore48_000615C8
   entry 0x080615C8, 24 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned int u32;

extern void f_08013404(u32 first, u32 second);

void f_target(void)
{
    f_08013404(0x080611B1u, 0x080611D1u);
}
