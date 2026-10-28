/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08064384.c
 * Original SHA-256: 36c52dd42db306176c6ad1283264c5ee5f8fdb9036cab3c54c9003f55300fd1c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct ScriptTaskState {
    u16 current;
    u16 count;
    u16 entries[32];
    void *task;
    u8 unknown_48[5];
    u8 unknown_4d;
} ScriptTaskState;

s16 func_08065050(const void *object);
void func_08066018(void *object);

void func_08064384(void)
{
    ScriptTaskState *state;

    if (func_08065050((*(ScriptTaskState **)0x0200F450)->task) != 0) {
        func_08066018((*(ScriptTaskState **)0x0200F450)->task);
        state = *(ScriptTaskState **)0x0200F450;
        state->current = state->entries[--state->count];
    }
}
