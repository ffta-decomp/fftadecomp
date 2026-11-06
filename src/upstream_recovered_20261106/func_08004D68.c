/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08004D68.c
 * Original SHA-256: fb383701ff65e7d11d35ed7e36053f1f0e0919d6810d6109fe84250e64f5413b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

extern u16 data_04000134;
extern u8 data_03002B60;
extern u8 data_030028A0;
extern u8 data_03002B44;
extern u8 data_03002884;

/* 0x08004D68 - 166 bytes, including literal pools. */
u8 func_08004D68(void)
{
    /* plausible: RCNT at 0x04000134 is a halfword MMIO hardware register. */
    volatile u16 *port = &data_04000134;
    u8 input = *port;

    if (data_03002B60 > 70)
        return 0;
    if (data_030028A0 & 8) {
        input &= 2;
        if (data_03002B44 & 1)
            *port = 0x8055;
        else
            *port = 0x8050;
    } else {
        input &= 5;
        if (data_03002B44 & 1)
            *port = 0x8022;
        else
            *port = 0x8020;
    }
    if (input == data_03002884) {
        data_03002B60++;
    } else {
        data_03002884 = input;
        data_03002B60 = 0;
    }
    data_03002B44 ^= 1;
    return 1;
}
