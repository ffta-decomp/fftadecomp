/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08142148.c
 * Original SHA-256: c415a5bd62d4bc34e128649bd3abad8d673d3d2251bbf91cc8e9c82a014d5e28
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* Complete [0x08142148,0x08142160), 24 bytes, 9 reached instructions.
 * The indirect call transports the incoming R0 word under ordinary ARM ABI. */
u32 func_08142148(void *argument, u32 (*callback)(void *))
{
    if (callback(argument))
        return 0x8004;
    return 0;
}
