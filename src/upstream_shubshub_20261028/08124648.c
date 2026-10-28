/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08124648.c
 * Original SHA-256: 694bede8668f8db91be1c403ac7a921040608e693c4b38792cdaee71fec73efa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

typedef struct {
    u32 unknown_00;
    SceneRecord *record;
} Binding;

typedef struct {
    SceneRecord first[24];
    u8 unknown_18C0[0x1684];
    SceneRecord second[12];
} State;

extern State g_state_02000080;

struct SceneObject;

void *func_08096D7C(void);
u8 func_080C95A8(u16 index);
void *func_0809A9C0(u8 *context, s32 index);
void *func_08099560(void *context, SceneRecord *record);
u32 func_080995C0(struct SceneObject *object);
Binding *func_08121C70(u8 selector);

void func_08124648(void)
{
    void *context = func_08096D7C();
    void *object;
    SceneRecord *record;
    Binding *binding;
    s32 index;
    s32 slot;

    if (func_080C95A8(13) == 1) {
        for (index = 0; index < 2; index++) {
            record = func_0809A9C0(func_08096D7C(), index);
            object = func_08099560(context, record);
            if (object != 0)
                func_080995C0(object);
        }
    }
    record = g_state_02000080.first;
    for (index = 23; index >= 0; index--, record++) {
        object = func_08099560(context, record);
        if (object != 0)
            func_080995C0(object);
    }
    record = g_state_02000080.second;
    for (index = 0; index < 12; index++, record++) {
        object = func_08099560(context, record);
        if (object != 0) {
            func_080995C0(object);
            for (slot = 0; slot < 16; slot++) {
                binding = func_08121C70(slot - 128);
                if (binding->record != 0 && binding->record == record) {
                    binding->record = 0;
                    break;
                }
            }
            (*(void (**)(void *, u32))0x0836D4B8)(record, sizeof(*record));
        }
    }
}
