/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08061564.c
 * Original SHA-256: 9e919955245c7debd03d0d3453167a4cece730c85c2fe179d05a26031746a363
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void func_0801174C(void *, u32, u8, void *, void *, u32, u32,
                          u32, u32, u32);
extern void func_0801339C(u32);
extern void func_08061188(void);
extern void func_0806119C(void);
extern void func_08013404(void (*)(void), void (*)(void));

/* Complete [0x08061564, 0x080615B0): 76 bytes, 27 instructions. */
void func_08061564(void *context, u8 index)
{
    func_0801174C(context, 1, index, data_030008B0, data_03000990,
                  2, 2, 0x18, 4, 0x3a0);
    func_0801339C(2);
    func_08013404(func_08061188, func_0806119C);
}
