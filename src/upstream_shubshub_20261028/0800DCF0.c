/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DCF0.c
 * Original SHA-256: 6b6de89e0336380c2e4ffcc37477263d07fb3f804cef8b0170d09c450e1a8e4f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800DCF0..0x0800DD10: 32 bytes / 13 instructions. */
struct State0800DCF0 {
    u8 unknown_00[0x34];
    u16 value;
};

extern struct State0800DCF0 *func_0800C614(void *object);
extern void func_0800C9E4(struct State0800DCF0 *state, u32 mode);
extern void func_0800C64C(void *object);

void func_0800DCF0(void *object, u16 value)
{
    struct State0800DCF0 *state = func_0800C614(object);

    state->value = value;
    func_0800C9E4(state, 0);
    func_0800C64C(object);
}
