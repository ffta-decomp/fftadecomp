/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08116CB0.c
 * Original SHA-256: 356f92b9cd05d5f6eb980e441eaa8ce0dc18a119464b494ade0ce82666abff3f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08116CB0, 0x08116F96), 742 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    u8 unknown_08[14];
    u16 flags;
} Descriptor08116CB0;

typedef struct {
    u8 flags;
    u8 selector;
    s16 x;
    s16 y;
    u16 delay;
    void *actor;
    void *underlying;
    void *wrapper;
    void *value;
    void *setup_task;
    u8 unknown_1c[24];
    void *effect_task;
    void *animation_task;
    void *record_task;
} Payload08116CB0;

extern const u8 data_083A4D1C[];
extern const void *const data_083A4FD4[];
extern const u8 data_083A4FF4[];
extern const u8 data_083A500C[];
extern const u8 data_083A4D64[];
extern const u8 data_083A5014[];
extern const u8 data_083A4EB4[];
extern const u8 data_083A501C[];
extern const u8 data_083A4FF8[];
extern const void *const data_083A4FE4[];
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void func_080DE390(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern u8 func_080DBC88(void *);
extern void func_080DBEB4(void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D6194(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DBA5C(void *);

u32 func_08116CB0(void *task, Descriptor08116CB0 *descriptor,
                  Payload08116CB0 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;

        payload->flags = descriptor->flags;
        payload->value = descriptor->value;
        mode = 6;
        if (payload->flags != 0)
            mode = 0;
        payload->setup_task = func_080E03F8(payload->value, data_083A4D1C,
                                           mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->setup_task = func_080E05DC(payload->setup_task);
        if (payload->setup_task != 0)
            break;
        if (func_080D3B54(payload->value)) {
            descriptor->phase = 2;
            break;
        }
        payload->actor = func_080DD47C(payload->value);
        func_080DE390(payload->actor);
        func_080DBDC8(payload->actor, &payload->x, &payload->y);
        payload->selector = func_080DBC88(payload->actor);
        payload->delay = 30;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->delay != 0)
            break;
        func_080DBEB4(payload->actor, 0);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1, 4,
            payload->unknown_1c, data_083A4FD4[payload->selector], task);
        func_080D6194(payload->effect_task, data_083A4FF4[payload->selector]);
        payload->record_task = func_080DFD8C(data_083A500C, 1, 4, 0, task);
        payload->delay = 20;
        descriptor->phase++;
        break;
    case 0x102:
        payload->effect_task = func_080D6134(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        if (payload->delay != 0 && --payload->delay != 0)
            break;
        payload->wrapper = func_080DD4A4(payload->value, 0);
        payload->underlying = func_080DD748(payload->wrapper,
            &payload->x, &payload->y, 0);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1, 6,
            payload->unknown_1c, data_083A4D64, task);
        payload->record_task = func_080DFD8C(data_083A5014, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        payload->effect_task = func_080D6134(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1, 4,
            payload->unknown_1c, data_083A4EB4, task);
        payload->record_task = func_080DFD8C(data_083A501C, 1, 4, 0, task);
        payload->delay = 40;
        descriptor->phase++;
        break;
    case 0x104:
        if (!func_080D8858(payload->value, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->effect_task = func_080D6134(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        if (payload->animation_task == 0)
            payload->animation_task = func_080DCFE4(payload->wrapper,
                data_083A4FF8, 12, 0, 12, task, 0);
        if (payload->delay != 0 && --payload->delay != 0)
            break;
        func_080DBDC8(payload->actor, &payload->x, &payload->y);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1, 4,
            payload->unknown_1c, data_083A4FE4[payload->selector], task);
        func_080D6194(payload->effect_task, data_083A4FF4[payload->selector]);
        payload->record_task = func_080DFD8C(data_083A500C, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        payload->effect_task = func_080D6134(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        func_080DBEB4(payload->actor, 1);
        payload->animation_task = func_080DBA5C(payload->animation_task);
        if (payload->animation_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
