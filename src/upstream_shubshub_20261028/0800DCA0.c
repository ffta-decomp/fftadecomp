/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DCA0.c
 * Original SHA-256: 5bb44ebd51570d5a26b8f0462e6b7d0454a191deb543f7275b4a31a4dc2d276f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800DCA0..0x0800DCC4: 36 bytes / 16 instructions. */
struct State0800DCA0 {
    u8 unknown_00[6];
    u16 first;
    u16 second;
};

extern struct State0800DCA0 *func_0800C614(void *object);
extern void func_0800C64C(void *object);

void func_0800DCA0(void *object, u16 first, u16 second)
{
    struct State0800DCA0 *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800C64C(object);
}
