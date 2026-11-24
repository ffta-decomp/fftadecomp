/* Contributed by gg; original source and attribution follow. */
/* Embedded42_00A39708
   entry 0x08A39708, 22 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
#include "ffta/unsigned_types.h"

void f_target(u8 *p, u8 a, u8 b, u8 c, u16 d, u8 e)
{
    p[0x17] = a;
    p[0x18] = b;
    p[0x19] = c;
    *(u16 *)(p + 0x1c) = d;
    p[0x1a] = e;
}
