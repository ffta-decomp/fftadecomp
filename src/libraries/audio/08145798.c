/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08145798.c
 * Original SHA-256: 2426f59eb083e192d1be7f224386b8148eba7f7fe286d850a1caa00a1209b6ab
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

extern u32 *data_03007FF0;
extern u32 data_040000C4;
extern u16 data_040000C6;
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target 08145798..081457FC, 100 bytes including literals. */
void func_08145798(void)
{
    u32 *sound = data_03007FF0;
    u32 zero;

    if (sound[0] - 0x68736D53u > 1)
        return;
    sound[0] += 10;
    if (data_040000C4 & 0x02000000)
        data_040000C4 = 0x84400004;
    data_040000C6 = 0x400;
    zero = 0;
    func_0814186C(&zero, sound + 0xD4, 0x0500018C);
}
