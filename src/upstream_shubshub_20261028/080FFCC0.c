/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FFCC0.c
 * Original SHA-256: bcde32fd4acaa34260ef53c1ad934200ab865965e64f0bd854e96f84b5dc0580
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080FFCC0, 0x080FFEBE), 510 bytes, 213 instructions. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080FFCC0;

typedef struct {
    u8 flag;
    u8 unknown_01;
    u16 countdown;
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_09[3];
    u8 unknown_0c[16];
    void *coordinate_task;
    void *actor;
    void *first_effect_task;
    void *second_effect_task;
    void *output;
    u32 coordinate_result;
    void *initial_task;
    void *object_task;
    void *output_task;
    void *sound_task;
} Payload080FFCC0;

extern const u8 data_0839E540[];
extern const u8 data_0839E5D8[];
extern const u8 data_0839E564[];
extern const u8 data_0894A5F0[];
extern const u8 data_0894AC40[];
extern const u8 data_0839E5C4[];
extern const u8 data_0839E5DC[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_080FFCC0(void *task, Descriptor080FFCC0 *descriptor,
                  Payload080FFCC0 *payload)
{
    void *actor;
    void *object;
    u8 mode;
    u8 actor_status;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 3;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_0839E540,
            mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        actor_status = func_080D3B54(payload->actor);
        if (actor_status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->output_task = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready, data_0839E5D8,
            5, actor_status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->countdown = 10;
        descriptor->phase++;
        break;
    case 0x102:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080DC12C(payload->actor, 0, 2);
        payload->countdown = 16;
        descriptor->phase++;
        break;
    case 0x103:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        if (func_080D8B4C())
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 4, payload->unknown_0c, data_0839E564, task);
        payload->first_effect_task = func_080D4704(data_0894A5F0, task);
        payload->second_effect_task = func_080D4704(data_0894AC40, task);
        payload->object_task = func_080DCFE4(object, data_0839E5C4,
            12, 36, 12, task, 36);
        payload->sound_task = func_080DFD8C(data_0839E5DC, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->first_effect_task = func_080D4774(payload->first_effect_task);
        if (payload->first_effect_task != 0)
            break;
        payload->second_effect_task = func_080D4774(payload->second_effect_task);
        if (payload->second_effect_task != 0)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        if (func_080DE244(payload->output) == 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
