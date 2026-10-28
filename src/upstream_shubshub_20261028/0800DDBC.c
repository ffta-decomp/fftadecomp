/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DDBC.c
 * Original SHA-256: 9cdce0009fd3fddb0fbc5516569ac18c62db9dc7c489e9d7aa37eda9bc356ce7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Effect0800DDBC {
    u8 unknown_00[0x1C];
};

extern void func_0800C720(struct Effect0800DDBC *effect,
                        u16 *destination, u8 stride);

void func_0800DDBC(struct Effect0800DDBC effects[2], u16 *destination)
{
    func_0800C720(&effects[0], destination, 4);
    func_0800C720(&effects[1], destination + 1, 4);
}
