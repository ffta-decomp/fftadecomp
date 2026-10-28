/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8B18.c
 * Original SHA-256: 966799b980448dbe41befb07e68456422c518e8bb30a44eb698c71ea755d5910
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D8B18..0x080D8B28: 16 bytes. */
typedef struct {
    u8 unknown_00[0x20];
    u32 value;
} HandleValueState;

extern HandleValueState *func_08005BFC(u32 handle);

void func_080D8B18(u32 handle, u32 value)
{
    HandleValueState *state = func_08005BFC(handle);

    state->value = value;
}
