/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DD88.c
 * Original SHA-256: 0231acf7cca5464adf87cc6de9981cf27533098c87127163258a42bf4f3db625
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x34];
    u16 first;
    u16 second;
} ValueState;

extern ValueState *func_0800C614(void *object);
extern void func_0800CBFC(ValueState *state);
extern void func_0800C64C(void *object);

/* 0800DD88..0800DDB0: 40 bytes. */
void func_0800DD88(void *object, u16 first, u16 second)
{
    ValueState *state = func_0800C614(object);

    state->first = first;
    state->second = second;
    func_0800CBFC(state);
    func_0800C64C(object);
}
