/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080DE818.c
 * Original SHA-256: e35307ae5094e9a7e06f4fe9d518d9bc4a9da75c4a1a2bc13c72017be4895934
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 delay;
} TaskDescriptor080DE818;

typedef struct {
    u16 phase_countdown;
    u16 initial_countdown;
    u8 previous_slot;
    u8 unknown_05[35];
    void *effect;
    void *object;
} TaskPayload080DE818;

extern u8 func_080DBC58(void *object, u8 value);
extern void *func_08147AD0(u16 first, u16 count, u16 duration);
extern void *func_081484CC(void *effect);
extern u16 func_080DD6F4(void *object);
extern void func_080DE10C(void *object, u16 action);
extern void *func_08147D2C(u16 first, u16 count, u16 duration, const u16 *colors);
extern s8 func_080DBC88(void *object);
extern void func_080DE33C(void *object, s8 value, u8 option);
extern u8 func_080DBC18(void *object, u8 value);

extern const u16 data_03003A60[][16];

static inline u8 normal_kind(u16 value)
{
    if (value == 8 || value == 15)
        return 0;
    return 1;
}

/* 0x080DE818 - 256 bytes.
 * Target: 70b50d1c141c298880204000814213d0814202dc002909d06ee00348814220d0
 *         013081424ad067e0010100006868e062a88a013060805fe06088013860800004
 *         002859d1e06a0c21fdf7faf92071e020400010210c2269f02ff9a06228880130
 *         49e0a06a69f026fea062002844d10c26e06afef733ff0004000c082801d00f28
 *         01d1002000e00120002800d14426e06a311cfff72ffc06202080e02040002379
 *         5b0105495b1810210c2269f033faa062288801301fe00000603a000320880028
 *         0ed0013820800004002815d1e06afdf7cff9011ce06a090609160022fff722fd
 *         a06a69f0e7fda062002805d1e06a2179fdf786f902202880002070bc02bc0847
 */
u32 func_080DE818(void *task, TaskDescriptor080DE818 *event,
                  TaskPayload080DE818 *state)
{

    switch (event->state) {
    case 0:
        state->object = event->object;
        state->initial_countdown = event->delay + 1;
        break;
    case 0x100:
        if (--state->initial_countdown == 0) {
            state->previous_slot = func_080DBC58(state->object, 12);
            state->effect = func_08147AD0(0x1C0, 16, 12);
            event->state++;
        }
        break;
    case 0x101:
        state->effect = func_081484CC(state->effect);
        if (state->effect == 0) {
            u16 action = 12;

            if (!normal_kind(func_080DD6F4(state->object)))
                action = 0x44;
            func_080DE10C(state->object, action);
            state->phase_countdown = 6;
            state->effect = func_08147D2C(0x1C0, 16, 12,
                data_03003A60[state->previous_slot]);
            event->state++;
        }
        break;
    case 0x102:
        if (state->phase_countdown != 0) {
            if (--state->phase_countdown != 0)
                break;
            {
                s8 selection = func_080DBC88(state->object);
                func_080DE33C(state->object, selection, 0);
            }
        }
        state->effect = func_081484CC(state->effect);
        if (state->effect == 0) {
            func_080DBC18(state->object, state->previous_slot);
            event->state = 2;
        }
        break;
    }
    return 0;
}
