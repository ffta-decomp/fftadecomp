/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FE920.c
 * Original SHA-256: 7f4b81cea1b0b82d69f49b212dcd4e1092b9dbec295e960a1a7e8856b6b5ce65
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080FE920 .. 0x080FEBDC: 700 bytes, 288 instructions.
 * Offset views describe the accesses in this callback, not original layouts.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    s16 classifier;
    u16 flag;
} Descriptor080FE920;

typedef struct {
    s16 x;
    s16 y;
    u16 counter;
    u8 mode;
    u8 flag;
    u8 status;
    u8 unknown_09[3];
    void *status_handle;
    void *coordinate_result;
    void *actor;
    void *initial_effect;
    u32 unknown_1c;
    void *optional_effect;
    void *resource;
    void *controller;
    void *child_2c;
    void *child_30;
    void *child_34;
    void *actor_effect;
    void *status_result;
    void *sound_result;
} Payload080FE920;

/* Only the observed byte and pointer reads are typed; extents are unknown. */
extern const u8 data_0839DDD0[];
extern const void *const data_0839DDC8[];
extern const u8 data_0839DE00[];
extern const u8 data_0839DE08[];
extern const u8 data_088EF09C[];
extern const u8 data_0894D7E4[];
extern const u8 data_08949AA0[];
extern const u8 data_08949AB4[];
extern const u8 data_08949AC8[];
extern const u8 data_0839DDD4[];
extern const u8 data_0839DDEC[];
extern const u8 data_0839DE0C[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void *, u16, u8, void *, const void *, u16, u16, void *);
extern u8 func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE1F0(void *);
extern void *func_080D6134(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern u8 func_080D48DC(void *, u16);
extern void *func_080DBA5C(void *);

u32 func_080FE920(void *task, Descriptor080FE920 *descriptor, Payload080FE920 *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        void *actor;
        u8 scalar;
        u16 flag;

        payload->mode = 0;
        if (descriptor->classifier == 0xb6)
            payload->mode = 1;
        flag = descriptor->flag;
        payload->flag = flag;
        actor = descriptor->actor;
        payload->actor = actor;
        scalar = data_0839DDD0[payload->mode];
        if ((u8)flag != 0)
            scalar = 0;
        payload->initial_effect = func_080E03F8(actor, data_0839DDC8[payload->mode], scalar, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_effect = func_080E05DC(payload->initial_effect);
        if (payload->initial_effect != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        if (payload->mode == 0)
            payload->status_result = func_080DDF68(payload->actor, &payload->status_handle, 52, 2,
                &payload->status, data_0839DE00, 0, 0, task);
        else
            payload->status_result = func_080DDF68(payload->actor, &payload->status_handle, 0x8007, 1,
                &payload->status, data_0839DE08, 5, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->status == 0)
            break;
        if (payload->mode == 0)
            payload->counter = 4;
        else {
            func_080DC12C(payload->actor, 0, 0);
            payload->counter = 20;
        }
        descriptor->phase++;
        break;
    case 0x102:
    {
        void *helper;
        u8 sound_count;

        if (payload->counter != 0 && --payload->counter != 0)
            break;
        if (func_080D8B4C())
            break;
        if (!func_080D8858(payload->actor, 0)) {
            descriptor->phase = 2;
            break;
        }
        helper = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(helper, &payload->x, &payload->y, 0);
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->resource = func_080D4B64(0, data_088EF09C, 0x3b9, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->controller = func_080D3E9C(data_0894D7E4, task);
        payload->child_2c = func_080D4704(data_08949AA0, task);
        payload->child_30 = func_080D4704(data_08949AB4, task);
        payload->child_34 = func_080D4704(data_08949AC8, task);
        sound_count = 1;
        if (func_080DD580(helper)) {
            payload->optional_effect = func_080D6098(payload->x, payload->y, 0, 1,
                1, &payload->unknown_1c, data_0839DDD4, task);
            sound_count = 2;
        }
        payload->actor_effect = func_080DCFE4(helper, data_0839DDEC, 12, 74, 4, task, 65);
        payload->sound_result = func_080DFD8C(data_0839DE0C, sound_count, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x103:
        if (!func_080DE1F0(payload->status_handle))
            break;
        payload->optional_effect = func_080D6134(payload->optional_effect);
        if (payload->optional_effect != 0)
            break;
        payload->resource = func_080D4D2C(payload->resource, 0);
        if (payload->resource != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->controller = func_080D3F08(payload->controller);
        if (payload->controller != 0)
            break;
        if (!func_080D48DC(&payload->child_2c, 3))
            break;
        payload->actor_effect = func_080DBA5C(payload->actor_effect);
        if (payload->actor_effect == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
