/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08063060.c
 * Original SHA-256: 2313c23b296a9547830cc33b4259dbda8fb8b7086ca526ff61f683207eadbab8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_000[0xC6E];
    u8 total;
    u8 count;
    u16 entries[4];
} SelectionState;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
} CommandState;

extern SelectionState g_state_02002FC4;
extern CommandState *data_0200F450;

/* Complete target: [0x08063060, 0x080630C4), 100 bytes, 42 instructions. */
void func_08063060(void)
{
    SelectionState *selection = &g_state_02002FC4;
    s32 index;

    selection->count = 0;
    for (index = 0; index < 4; index++) {
        if (selection->entries[index] != 0)
            selection->count++;
    }
    selection->total = selection->count + 1;
    data_0200F450->current = data_0200F450->entries[--data_0200F450->count];
}
