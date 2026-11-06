/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08003E88.c
 * Original SHA-256: b2b7c3c6c41a04d5329f913300c7cf8f0834c84194789c4cfd04192f0082ee76
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

extern u8 data_030028A0[];
extern u16 data_03002B50;
extern u8 data_03002B52[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_081444B8(const void *input);

/* Complete [0x08003E88, 0x08003F10): 136 bytes, 53 instructions. */
u32 func_08003E88(const u8 *input)
{
    u8 *destination = data_03002B52;
    u16 zero;
    s32 index;

    if (data_030028A0[0x124] != 1)
        return 0;
    data_030028A0[0x124] = 2;
    zero = 0;
    func_0814186C(&zero, destination, 0x01000006);
    *((u16 *)destination - 1) =
        func_081444B8(input) > 11 ? 12 : func_081444B8(input);
    for (index = 0; index < data_03002B50; ++index)
        *destination++ = *input++;
    data_030028A0[0x124] = 10;
    return 1;
}
