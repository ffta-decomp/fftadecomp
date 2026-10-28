/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8DC0.c
 * Original SHA-256: 4963ba1186490db79521640fd931b9543fc4517ae9dbe557f7a367331523e3a1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_08141570(u32 mode, u16 id);
extern void func_08141520(u16 id);

/* Complete [0x080D8DC0, 0x080D8E00): 64 bytes, 30 instructions. */
void func_080D8DC0(u16 flags)
{
    u32 mode = 0;

    if (flags & 1)
        return;
    if (flags & 2)
        mode = 1;
    else if (flags & 4)
        mode = 2;
    if (mode != 0)
        func_08141570(mode, 0x8D);
    else
        func_08141520(0x8D);
}
