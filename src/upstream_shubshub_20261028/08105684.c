/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08105684.c
 * Original SHA-256: 187dc72e0ce48bf187179ad87fb4caa615f7874c3e98af5c573781461d5650dd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08105684, 0x0810578C), 264 bytes, 108 instructions.
 * These are offset views, not recovered original object declarations or extents.
 * Helper returns, storage effects, ABI preservation and lifetime remain opaque.
 * Later phases and the initial values of both counters are separate premises. */

typedef struct {
    u16 phase;
    u8 unknown_02[18];
    u16 selector;
} Descriptor08105684;

typedef struct {
    u8 selector;
    u8 unknown_01[3];
    s16 counter_04;
    s16 counter_06;
    void *initial_task;
    void *object_task;
    void *coordinate_task;
    void *sound_task;
} Payload08105684;

/* Observed addresses only; the selector views have no inferred bounds. */
extern const u8 data_0894D8EC[];
extern const void *const data_0839FD8C[];
extern const void *const data_0839FDAC[];
extern const u8 data_0839FDCC[];
extern const u8 data_0839FDE0[];
extern u16 g_control_flags_03000940;

extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080D7220(const void *, u8, u8, u16, u16, u16);
extern void *func_080D979C(u8, u8, u8, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D987C(void *, u8, s32);
extern void func_08003558(s32, u8);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(u8);
extern void *func_080D4774(void *);
extern void *func_080D9B64(void *);

u32 func_08105684(void *task, Descriptor08105684 *descriptor,
                  Payload08105684 *payload)
{
    u32 mask;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        break;
    case 1:
        break;
    case 0x100:
        payload->initial_task = func_080D3E9C(data_0894D8EC, task);
        payload->object_task = func_080D4704(
            data_0839FD8C[payload->selector], task);
        func_080D7220(data_0839FDAC[payload->selector], 0, 2, 0, 0, 0);
        payload->coordinate_task = func_080D979C(0, 2, 0, data_0839FDCC, task);
        payload->sound_task = func_080DFD8C(data_0839FDE0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->counter_04 -= 2;
        payload->counter_06--;
        func_080D987C(payload->coordinate_task, 0, payload->counter_04 >> 1);
        func_08003558(payload->counter_06 >> 1, 2);
        payload->initial_task = func_080D3F08(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        mask = func_080035A8(2);
        g_control_flags_03000940 &= ~mask;
        payload->object_task = func_080D4774(payload->object_task);
        if (payload->object_task != 0)
            break;
        payload->coordinate_task = func_080D9B64(payload->coordinate_task);
        if (payload->coordinate_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
