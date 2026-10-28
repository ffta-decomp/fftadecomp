/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080664E0.c
 * Original SHA-256: 0403678f879431add5c1652fabc7103490df94a79449a490da3535535192c269
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 first;
    u16 second;
} Range080664E0;

typedef struct {
    u8 unknown_000[0x424];
    void *entries[0x178];
    Range080664E0 modes[8];
    Range080664E0 types[0];
} Root080664E0;

typedef struct {
    Root080664E0 *root;
    u8 unknown_04[4];
    u8 mode;
    u8 id;
    u8 unknown_0a;
    s8 selection;
    u8 unknown_0c[4];
    void *value;
    u8 unknown_14[0xa0];
    u8 types[0];
} State080664E0;

extern u8 func_080099A4(u8);
extern void func_08066ED8(State080664E0 *);
extern void *func_0806517C(u8, void *, State080664E0 *);
extern void func_080669B4(State080664E0 *);

/* Complete [0x080664E0, 0x08066570): 144 bytes, 61 instructions. */
u8 func_080664E0(State080664E0 *state)
{
    if (func_080099A4(state->id)) {
        func_08066ED8(state);
        if (state->mode == 7 || state->mode == 4) {
            Range080664E0 *range;

            if (state->mode == 7)
                range = &state->root->modes[state->mode];
            else
                range = &state->root->types[state->types[state->selection]];
            state->value = func_0806517C(state->mode,
                state->root->entries[range->first + range->second], state);
        }
        if (state->mode == 5 || state->mode == 6)
            func_080669B4(state);
        return 1;
    }
    return 0;
}
