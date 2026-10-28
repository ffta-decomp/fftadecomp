/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0811A97C.c
 * Original SHA-256: 0602d7e11425871feef39224f89d6ef8e5a551ec9a133652ebf1db157a491539
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0811A97C, 0x0811AB42), 454 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0e];
    u16 variant;
} Descriptor0811A97C;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation0811A97C;

typedef struct {
    u8 variant;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *actor;
    void *actor_object;
    void *coordinate_result;
    void *sprite;
    void *timeline;
    void *initial_task;
    void *effect_task;
    void *record_task;
    Interpolation0811A97C motion;
} Payload0811A97C;

extern const u8 data_083A67B4[];
extern const u8 data_088F3604[];
extern const u8 data_0894DEA8[];
extern const u8 data_083A67E0[];
extern const u8 data_083A67CC[];
extern const u8 data_083A67E8[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080E0608(Interpolation0811A97C *, s16, s16, s16);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080E0690(Interpolation0811A97C *);
extern void func_080E064C(Interpolation0811A97C *);
extern void func_0800BC08(u32, s16, s16);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DD580(void *);
extern void *func_080DBA5C(void *);

u32 func_0811A97C(void *task, Descriptor0811A97C *descriptor,
                  Payload0811A97C *payload)
{
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 2;
        if (payload->variant != 0)
            animation = 0;
        payload->initial_task = func_080E03F8(payload->actor, data_083A67B4,
                                              animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
                                                   &payload->x, &payload->y, 0);
        func_080E0608(&payload->motion, payload->y - 8, payload->y + 24, 60);
        func_080D49FC(0, 2, 0, payload->x, payload->motion.current);
        payload->sprite = func_080D4B64(0, data_088F3604, 964, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->timeline = func_080D3E9C(data_0894DEA8, task);
        payload->record_task = func_080DFD8C(data_083A67E0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (func_080E0690(&payload->motion) == 0) {
            func_080E064C(&payload->motion);
            func_0800BC08(0, payload->x, payload->motion.current);
        }
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->effect_task = func_080DCFE4(payload->actor_object,
                                            data_083A67CC, 12, 0, 4, task, 0);
        if (func_080DD580(payload->actor_object))
            payload->record_task = func_080DFD8C(data_083A67E8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
