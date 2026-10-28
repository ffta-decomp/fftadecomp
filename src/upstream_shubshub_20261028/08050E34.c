/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08050E34.c
 * Original SHA-256: 614c5041302b59de160d31ea78d3956bfa32d42399242d3624395abf7b9f6771
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
} Control;

typedef struct {
    u8 unknown_00[0x68];
    Control control;
} ControlState;

extern void func_08017D18(Control *control, u8 flags);

/* 08050E34..08050E52: 30 bytes, 14 instructions. */
void func_08050E34(ControlState *state)
{
    u8 flags = state->control.flags & 4;

    func_08017D18(&state->control, flags | 3);
}
