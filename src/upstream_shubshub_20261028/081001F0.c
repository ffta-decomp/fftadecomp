/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081001F0.c
 * Original SHA-256: 7df28c251a7a4064eb89a345f924fd1f2dd6dba58b1a596810c03aa3c98df34a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x081001F0..0x081004B8: 712 bytes, 306 instructions. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor081001F0;

typedef struct {
    s16 x;
    s16 y;
    u16 counter;
    u8 flag;
    u8 property;
    u8 mode;
    u8 ready;
    u16 unknown_0a;
    void *output;
    void *coordinate_result;
    void *actor_object;
    void *actor;
    void *initial_child;
    u32 unknown_20;
    u32 unknown_24;
    void *position_child;
    void *effect_child;
    void *output_child;
    void *final_child;
} Payload081001F0;

extern const u8 data_0839E6D0[];
extern const u8 data_0839E76C[];
extern const u8 data_0839E6F4[];
extern const u8 data_0839E774[];
extern const u8 data_0839E724[];
extern const u8 data_0839E77C[];
extern const u8 data_0839E754[];
extern const u8 data_0839E784[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern void *func_080DD4B4(void *, u8);
extern u8 func_080DC0BC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern s8 func_080DBC88(void *);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s32, s32, s32, s32, s32, void *,
                         const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D6194(void *, u8);
extern void *func_080D6134(void *);
extern void *func_080DCFE4(void *, const void *, u8, s16, s16, void *, s16);
extern void *func_080DF7A0(void *, u8, u8, u8, u16, void *);
extern void *func_080DBA5C(void *);
extern void func_080DBEB4(void *, u8);
extern u8 func_080DE1F0(void *);

u32 func_081001F0(void *task, Descriptor081001F0 *descriptor,
                  Payload081001F0 *payload)
{
    void *actor;
    u8 animation;
    u8 actor_status;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 3;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_0839E6D0,
                                               animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        actor_status = func_080D3B54(payload->actor);
        if (actor_status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->output_child = func_080DDF68(payload->actor, &payload->output,
            0x8007, 2, &payload->ready, data_0839E76C, 5, actor_status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DC0BC(func_080DD4B4(payload->actor, 0), 1);
        descriptor->phase++;
        /* Fall through: readiness is checked in the same invocation. */
    case 0x102:
        if (func_080D8B4C() != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        payload->property = func_080DBC88(payload->coordinate_result);
        payload->mode = func_080DD580(payload->actor_object);
        if (payload->mode != 0) {
            payload->position_child = func_080D6098(payload->x, payload->y,
                0, 1, 2, &payload->unknown_20, data_0839E6F4, task);
            payload->final_child = func_080DFD8C(data_0839E774, 1, 4, 0, task);
        } else {
            payload->position_child = func_080D6098(payload->x, payload->y,
                0, 1, 2, &payload->unknown_20, data_0839E724, task);
            payload->final_child = func_080DFD8C(data_0839E77C, 1, 4, 0, task);
        }
        if (payload->property > 1)
            func_080D6194(payload->position_child, 1);
        descriptor->phase++;
        break;
    case 0x103:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        if (payload->mode == 0) {
            payload->effect_child = func_080DCFE4(payload->actor_object,
                0, 12, 0, 12, task, 0);
            descriptor->phase = 0x106;
            break;
        }
        payload->effect_child = func_080DF7A0(payload->coordinate_result,
            6, payload->property > 1 ? 1 : 0, 4, 0, task);
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, &payload->unknown_20, data_0839E754, task);
        if (payload->property > 1)
            func_080D6194(payload->position_child, 1);
        descriptor->phase++;
        break;
    case 0x104:
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        payload->counter = 20;
        payload->final_child = func_080DFD8C(data_0839E784, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        --payload->counter;
        if (payload->counter & 1)
            func_080DBEB4(payload->coordinate_result, 1);
        else
            func_080DBEB4(payload->coordinate_result, 0);
        if (payload->counter == 0)
            descriptor->phase++;
        break;
    case 0x106:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        if (func_080DE1F0(payload->output) == 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
