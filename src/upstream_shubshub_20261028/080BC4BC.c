/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BC4BC.c
 * Original SHA-256: fecbe969ac1616fd3fc2159453097fa5d9ccc413307144214ff167a0b6066fab
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *record;
} Entry080BC4BC;

typedef struct Context080BC4BC Context080BC4BC;

typedef struct {
    Context080BC4BC *context;
    Entry080BC4BC *entries[13];
    u8 unknown_38;
    u8 count;
    u8 unknown_3A[2];
    void *workspace;
    u16 current;
    u16 history_count;
    u16 history[34];
} State080BC4BC;

typedef void (*ClearBuffer080BC4BC)(void *destination, u32 size);

extern ClearBuffer080BC4BC const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern s32 func_08099CDC(Context080BC4BC *context, Entry080BC4BC **entries);
extern u8 func_080C8280(const void *record);
extern u8 func_080C8240(void *record);
extern u8 func_080C8260(const void *record);
extern u8 func_080CDCEC(const void *record);

/* Complete [0x080BC4BC, 0x080BC584): 200 bytes, 89 instructions. */
void func_080BC4BC(State080BC4BC *state, Context080BC4BC *context)
{
    Entry080BC4BC **entries;
    s32 count;
    s32 index;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    entries = func_08022840(13 * sizeof(*entries));
    state->context = context;
    count = func_08099CDC(context, entries);
    for (index = 0; index < count; index++) {
        if (func_080C8280(entries[index]->record) &&
            !func_080C8240(entries[index]->record) &&
            !func_080C8260(entries[index]->record) &&
            !func_080CDCEC(entries[index]->record)) {
            state->entries[state->count++] = entries[index];
        }
    }
    func_08022854(entries);
    state->current = 9;
    if (state->count != 0) {
        state->workspace = func_08022840(0x50);
        state->history[state->history_count++] = state->current;
        state->current = 0;
    }
}
