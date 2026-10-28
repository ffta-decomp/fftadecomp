/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD708.c
 * Original SHA-256: 3d570087aa1832fe40972a6f70cd11d4d683faa0f8d7490b618c1638936c9acc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Owner080DD708 {
    const void *object;
};

extern s32 func_080C7EA4(const void *object, u32 selector);

u16 func_080DD708(const struct Owner080DD708 *owner)
{
    return func_080C7EA4(owner->object, 4);
}
