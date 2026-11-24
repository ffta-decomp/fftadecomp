/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08089C84.c
 * Original SHA-256: ab38569c07cc0600ec54fd04a83b854dc78db5f36b261614648cb9e0f9571d2a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[6];
    u16 flags_06;
} DisplayState08089C84;

typedef struct {
    u8 unknown_00[0x10];
    void (*callback_10)(void);
} DisplayCallbacks08089C84;

extern void func_0808A1E8(void);
extern u8 data_030027A4;
extern DisplayCallbacks08089C84 data_030008D0;
extern DisplayState08089C84 data_03000EA0;

/* Complete target [0x08089C84, 0x08089CAC): 40 bytes, 12 instructions. */
void func_08089C84(void)
{
    data_030027A4 = 0xFF;
    data_030008D0.callback_10 = func_0808A1E8;
    data_03000EA0.flags_06 |= 4;
}
