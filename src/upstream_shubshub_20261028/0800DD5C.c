/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DD5C.c
 * Original SHA-256: 17e42e8e953deb6f3d052bf8664b3c23d4a06e4976dd182138c6e0e0b7ef4eb1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct State0800DD5C {
    u8 unknown_00[0x34];
    u16 first;
    u16 second;
} State0800DD5C;

extern State0800DD5C *func_0800C614(void *object);
extern void func_0800CAF0(State0800DD5C *state, u32 mode);
extern void func_0800C64C(void *object);

/* Complete [0x0800DD5C, 0x0800DD86): 42 bytes, 18 instructions. */
void func_0800DD5C(void *object, u16 first, u16 second)
{
    State0800DD5C *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800CAF0(state, 1);
    func_0800C64C(object);
}
