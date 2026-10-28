/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080921B4.c
 * Original SHA-256: ab93a1797a8102a14a86c99ff20d21ab05b62552aca8b9fa175d8247ecb47d7e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x144];
    u8 handle;
} Unit080921B4;

typedef struct {
    Unit080921B4 *unit;
} Context080921B4;

extern void func_08000D90(s32 handle);

/* Complete [0x080921B4, 0x080921C8): 20 bytes, 9 instructions. */
void func_080921B4(Context080921B4 *context)
{
    func_08000D90(context->unit->handle);
}
