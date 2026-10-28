/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EBC0.c
 * Original SHA-256: ee7664771dcf0c79183176557eb6faaba0225f2138584c65e98fb38098e0b56d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813EBC0..0x0813EC04: 68 bytes, 31 instructions. */
typedef struct {
    u8 active;
    u8 kind;
    u8 unknown_02[2];
    u8 first[0x10];
    u8 second[8];
    u32 field_1C;
    u32 field_20;
} State;

extern void func_0814186C(const void *source, void *destination, u32 count);
extern void func_0813DC3C(void *destination, u8 kind);

void func_0813EBC0(State *state, const void *source, u8 kind)
{
    func_0814186C(source, state->first, 4);
    func_0814186C(source, state->second, 4);
    state->field_20 = 0;
    state->field_1C = 0;
    state->kind = kind;
    state->active = 0;
    func_0813DC3C(state->first, state->kind);
}
