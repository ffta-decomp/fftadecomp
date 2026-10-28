/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08122CA8.c
 * Original SHA-256: 95699c900c94284a177fd1e04558a3ca988e16b029a0aff3eb620a62e8c9193a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} Children08122CA8;

extern Children08122CA8 *func_081255C8(u8 index);
extern void (*data_08394034)(void *object, u8 value, u32 first, u32 second,
                             u32 third, u32 fourth);

/* 0x08122CA8: 92 bytes; apply a command value to the selected children. */
u32 func_08122CA8(void *unused, const u8 *command)
{
    Children08122CA8 *state = func_081255C8(command[1]);
    u8 value = command[2];

    data_08394034(state->first, value, 0, 0, 0, 0);
    if (state->second)
        data_08394034(state->second, value, 0, 0, 0, 0);
    return 0x110;
}
