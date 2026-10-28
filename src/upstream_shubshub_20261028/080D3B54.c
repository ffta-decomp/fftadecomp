/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D3B54.c
 * Original SHA-256: f3c5738017be5daa12f7c28d3c709bc92daaeac51f5306ba0bc39c1016a4c1b5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 flags;
} State;

extern State *func_080A880C(void *object);
extern u8 func_080DD698(void *object, u32 mask);
extern u8 func_080DD494(void *object);

static inline u8 has_blocking_flag(void *object)
{
    State *state = func_080A880C(object);

    if (state->flags & 8)
        return 1;
    return 0;
}

u8 func_080D3B54(void *object)
{
    if (!has_blocking_flag(object) && !func_080DD698(object, 0x20) &&
        !func_080DD494(object))
        return 1;
    return 0;
}
