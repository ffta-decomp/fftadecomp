/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DE20.c
 * Original SHA-256: 0128acf7ddee0c67d6de68f51c71ea8787f405b1cb44f6064f71925f04c9d263
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Effect0800DE20 {
    u8 unknown_00[0x1C];
};

extern void func_0800C804(struct Effect0800DE20 *effect,
                        u16 *destination, u8 stride);

void func_0800DE20(struct Effect0800DE20 effects[2], u16 *destination)
{
    func_0800C804(&effects[0], destination, 4);
    func_0800C804(&effects[1], destination + 1, 4);
}
