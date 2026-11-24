/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080CC8D0.c
 * Original SHA-256: 214dfae55076a5ef46332e5144553d61390089fc7a1090b5995e9e7aae866416
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

extern u8 func_080CECF4(void);
extern u8 func_080C95A8(u16 index);
extern void func_080C95C0(u16 index, u32 value);
extern u16 func_080CC9F0(u8 table, u8 index);

/* Complete [0x080CC8D0, 0x080CC956): 134 bytes. */
u32 func_080CC8D0(u8 table)
{
    u16 slot;
    u8 count;
    u8 index;

    switch (table) {
    case 2: slot = 14; break;
    case 3: slot = 15; break;
    case 4: slot = 16; break;
    case 5: slot = 17; break;
    case 6: slot = 18; break;
    }
    count = func_080CECF4();
    index = func_080C95A8(slot);
    if (count > index) {
        func_080C95C0(slot, count);
        for (index++; index <= count; index++) {
            if (func_080CC9F0(table, index))
                return 1;
        }
    }
    return 0;
}
