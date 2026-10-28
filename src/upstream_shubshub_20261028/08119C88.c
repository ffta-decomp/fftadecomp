/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08119C88.c
 * Original SHA-256: df2f3be898b0100c8a001cfb8d054b23babc82721cadbf4010ea98c03d73d3b2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 state;
    u16 unknown_02;
    void *resource;
    u8 unknown_08[12];
    u16 flags;
} Event08119C88;

typedef struct {
    u8 flags;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *position_handle;
    void *resource;
    u32 effect_data;
    void *effect_handle;
    void *animation_handle;
    void *object_handle;
} State08119C88;

extern const u8 data_083A6530[];
extern const u8 data_083A6564[];
extern const u8 data_083A6548[];

extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void *func_080D6098(int, int, int, int, int, u32 *, const void *, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080DCFE4(void *, const void *, int, int, int, void *, int);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* 0x08119C88 .. 0x08119D74: 236 target bytes. */
int func_08119C88(void *owner, Event08119C88 *event, State08119C88 *state)
{
    int flags;

    switch (event->state) {
    case 0:
        state->flags = event->flags;
        state->resource = event->resource;
        state->position_handle = func_080DD748(state->resource, &state->x, &state->y, 0);
        break;
    case 0x100:
        state->effect_handle = func_080D6098(state->x, state->y, 0, 1, 1,
                                             &state->effect_data, data_083A6530, owner);
        flags = (state->flags & 1) ? 16 : 8;
        state->object_handle = func_080DFD8C(data_083A6564, 1, flags | 4, 0, owner);
        flags = (state->flags & 1) ? 4 : 2;
        state->animation_handle = func_080DCFE4(state->resource, data_083A6548,
                                                12, 30, flags, owner, 30);
        event->state++;
        break;
    case 0x101:
        state->effect_handle = func_080D6134(state->effect_handle);
        if (!state->effect_handle)
            event->state++;
        break;
    case 0x102:
        state->animation_handle = func_080DBA5C(state->animation_handle);
        if (!state->animation_handle)
            event->state = 2;
        break;
    }
    return 0;
}
