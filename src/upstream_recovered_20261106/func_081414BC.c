/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/081414BC.c
 * Original SHA-256: f464a2b485351349c91ba922c1ac854ad24770c791a92f06f82f8324e62ae6a6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

extern u8 data_020084D8;
extern void func_0814513C(void);
extern void func_081456AC(u32 mode);
extern void func_08145798(void);

/* Complete [0x081414BC, 0x081414F0), 52 bytes. */
void func_081414BC(void)
{
    data_020084D8 = 0xFF;
    *(u16 *)0x020084D4 = 0xFFFF;
    func_0814513C();
    func_081456AC(0x95C880);
    func_08145798();
}
