/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08010FD0.c
 * Original SHA-256: ac92c79097cafa3a8af52d8a8378bf36b60758a4289cd0043a50dd1e5a30a062
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct BufferState08010FD0 {
    u8 unknown_00[0x18];
    u8 data[0x20];
} BufferState08010FD0;

extern void (*const data_0836D4BC)(void *destination, const void *source,
                                  s32 size);

/* Complete [0x08010FD0, 0x08010FEC): 28 bytes, 11 instructions. */
void func_08010FD0(const BufferState08010FD0 *state, void *destination)
{
    data_0836D4BC(destination, state->data, sizeof(state->data));
}
