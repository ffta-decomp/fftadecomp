/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DD10.c
 * Original SHA-256: ba15690cec0a457b4e6e99c1f04757fc02414da1430e80bb13d483b9ca82fa00
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x34];
    u16 value;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800C9E4(ValueState *state, u32 mode);
extern void func_0800C64C(void *object);

/* 0800DD10..0800DD30: 32 bytes, 13 instructions. */
void func_0800DD10(void *object, u16 value)
{
    ValueState *state = func_0800C614(object);

    state->value = value;
    func_0800C9E4(state, 1);
    func_0800C64C(object);
}
