/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DDDC.c
 * Original SHA-256: 94400de26e3d1e614d9f1a5f7c9fe2f69e5a8dd3faeb7c6f1cc7ab97e47ffaf3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Effect0800DDDC;

extern void func_0800C720(Effect0800DDDC *effect,
                         u16 *destination, u8 stride);

/* Complete [0x0800DDDC, 0x0800DE14): 56 bytes, 24 instructions. */
void func_0800DDDC(Effect0800DDDC effects[4], u16 *destination)
{
    func_0800C720(&effects[0], destination, 8);
    func_0800C720(&effects[1], destination + 1, 8);
    func_0800C720(&effects[2], destination + 2, 8);
    func_0800C720(&effects[3], destination + 3, 8);
}
