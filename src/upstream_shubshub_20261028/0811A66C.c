/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0811A66C.c
 * Original SHA-256: 82108d598dd74e5797ef25511bc6d087e6f48fe6c7984801ad95924a99dc6196
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Descriptor0811A66C {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flags;
};

struct Payload0811A66C {
    u8 flags;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *actor_object;
    void *position_task;
    u32 effect_data[3];
    void *effect_task;
    void *child;
    void *initial_task;
    void *actor;
    void *animation_task;
    void *record_task;
};

extern const u8 data_083A66C8[];
extern const u8 data_088F66D4[];
extern const u8 data_0894DE80[];
extern const u8 data_083A66F8[];
extern const u8 data_083A6740[];
extern const u8 data_083A6754[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(u8);
extern void *func_080DBA5C(void *);

/* Target: complete [0x0811A66C, 0x0811A7C0), 340 bytes. */
u32 func_0811A66C(void *task, struct Descriptor0811A66C *descriptor,
                  struct Payload0811A66C *payload)
{
    u8 animation;
    void *initial_task;

    switch (descriptor->phase) {
    case 0:
        payload->flags = descriptor->flags;
        payload->actor = descriptor->actor;
        animation = 4;
        if (payload->flags != 0)
            animation = 0;
        payload->initial_task = func_080E03F8(payload->actor, data_083A66C8,
                                                animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        initial_task = func_080E05DC(payload->initial_task);
        payload->initial_task = initial_task;
        if (initial_task != 0)
            break;
        if (!func_080D8858(payload->actor, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->position_task = func_080DD748(payload->actor_object,
                                                &payload->x, &payload->y, 0);
        func_080D7220(data_088F66D4, 0, 2, payload->x, payload->y, (u32)initial_task);
        payload->child = func_080D3E9C(data_0894DE80, task);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1, 3,
                                             payload->effect_data, data_083A66F8, task);
        payload->animation_task = func_080DCFE4(payload->actor_object,
                                                  data_083A6740, 12, 40, 4, task, 40);
        payload->record_task = func_080DFD8C(data_083A6754, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->effect_task = func_080D6134(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        payload->child = func_080D3F08(payload->child);
        if (payload->child != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->animation_task = func_080DBA5C(payload->animation_task);
        if (payload->animation_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
