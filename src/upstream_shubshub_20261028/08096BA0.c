/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08096BA0.c
 * Original SHA-256: 6794eed3c0e20914ebfbdbb44b2c46280c177da0f6cb3fbd5636803305296b6a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *context;
    u8 unknown_04[0x40];
    void *child;
    u8 unknown_48[0x80];
    u8 active;
    u8 unknown_C9[7];
    u32 flags;
    u8 unknown_D4[8];
    u16 count;
    u8 unknown_DE[0xDA];
} State08096BA0;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} ScriptControl08096BA0;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit08096BA0;

typedef struct {
    Unit08096BA0 units[24];
    u8 unknown_18C0[0x1684];
    Unit08096BA0 reserve[12];
} Units08096BA0;

typedef void (*BufferInitializer08096BA0)(void *destination, u32 bytes);

extern void *data_0200F4AC;
extern State08096BA0 data_0200F4E8;
extern State08096BA0 *data_0200F4A8;
extern ScriptControl08096BA0 g_state_0200F390;
extern Units08096BA0 g_state_02000080;
extern BufferInitializer08096BA0 g_callbacks_0836D4B8[];

extern void func_080BD02C(void);
extern void func_080A925C(void);
extern void func_080A94B8(void);
extern void *func_08022840(u32 bytes);
extern void *func_080070C8(void *storage, u32 bytes);
extern void func_0808F770(void);
extern void func_08096ED4(void);
extern void *func_08096D7C(void);
extern void *func_0809D428(void);
extern void func_0809A5C0(void *context, u8 enabled);
extern u8 func_080C95A8(u16 index);
extern void func_080C7240(void);
extern void func_080C7260(void);

static inline State08096BA0 *initialize_state(void *context)
{
    State08096BA0 *state = &data_0200F4E8;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->child = func_0809D428();
    state->context = context;
    state->count = 8;
    state->active = 0;
    func_0809A5C0(context, 1);
    if (func_080C95A8(13))
        state->flags |= 0x800;
    return state;
}

static inline void clear_unit_flags(void)
{
    Unit08096BA0 *unit = g_state_02000080.units;
    Unit08096BA0 *reserve = g_state_02000080.reserve;

    {
        u32 mask = 0xFFFE;
        int i;

        for (i = 23; i >= 0; --i, ++unit)
            unit->flags &= mask;
    }
    unit = reserve;
    {
        u32 mask = 0xFFFE;
        int i;

        for (i = 11; i >= 0; --i, ++unit)
            unit->flags &= mask;
    }
}

/* 0x08096BA0..0x08096CB8: 280 bytes, 107 instructions. */
void func_08096BA0(void)
{
    void *context;
    void **storage;

    func_080BD02C();
    func_080A925C();
    func_080A94B8();
    storage = &data_0200F4AC;
    *storage = func_08022840(0x4500);
    g_callbacks_0836D4B8[0](*storage, 0x4500);
    func_080070C8(*storage, 0x4400);
    func_0808F770();
    func_08096ED4();
    context = func_08096D7C();
    data_0200F4A8 = initialize_state(context);

    if (!(g_state_0200F390.flags & 0x80))
        clear_unit_flags();
    g_state_0200F390.flags |= 1;
    func_080C7240();
    if (func_080C95A8(13))
        func_080C7260();
}
