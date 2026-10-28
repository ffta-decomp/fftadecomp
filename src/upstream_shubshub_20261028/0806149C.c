/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806149C.c
 * Original SHA-256: 786b2e39acd68d2f3fd91cc6120ad9f3379eab24968baed52d8a94036337e0e9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 *object;
} DisplayState;

extern DisplayState data_030008B0;
extern void func_08016A98(void *object, u32 first, u32 second, u32 third, u32 fourth);

/* Complete target: [0x0806149C, 0x080614C4), 40 bytes, 17 instructions. */
void func_0806149C(u8 enabled)
{
    if (enabled)
        func_08016A98(data_030008B0.object + 0x74, 3, 2, 0, 0x20);
}
