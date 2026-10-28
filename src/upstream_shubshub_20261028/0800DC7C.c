/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DC7C.c
 * Original SHA-256: a69f6fffeb189f0d90e0dcfed584947548f096dca7aef503c151e0fccf5d0f38
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 first;
    u16 second;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800C64C(void *object);

/* 0800DC7C..0800DCA0: 36 bytes. */
void func_0800DC7C(void *object, u16 first, u16 second)
{
    ValueState *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800C64C(object);
}
