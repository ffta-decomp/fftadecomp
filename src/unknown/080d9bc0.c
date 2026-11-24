/* Contributed by gg; original source and attribution follow. */
asm(".global f_08141864\n.thumb_set f_08141864,0x08141865\n");
/* RemainingBand43_000D9BC0
   entry 0x080D9BC0, 12 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned int u32;

extern void f_08141864(const void *source, void *destination, u32 control);

void f_target(const void *source, void *destination)
{
    f_08141864(source, destination, 160U);
}
