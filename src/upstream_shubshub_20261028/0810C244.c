/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810C244.c
 * Original SHA-256: e68e2a3c18d3cb77cfa274d80e72ebdde982b3c103a48da1344143c635cf5ed7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810C244, 0x0810C4D4), 656 bytes, 271 instructions.
 * Local offset views; original declarations and storage extents are unknown.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 flag;
} Descriptor0810C244;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 mode;
    u8 flag;
    u8 ready;
    u8 unknown_09[3];
    void *output;
    void *coordinate_result;
    void *actor_object;
    void *actor;
    void *initial_task;
    u8 unknown_20[0x14];
    void *coordinate_task;
    void *resource_task;
    void *first_task;
    void *second_task;
    void *object_task;
    void *output_task;
    void *record_task;
} Payload0810C244;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A2310[];
extern const u8 data_083A23B8[];
extern const u8 data_083A23B0[];
extern const u8 data_083A23AC[];
extern const u8 data_088F2BF0[];
extern u16 g_control_flags_03000940;
extern const u8 data_0894D690[];
extern const u8 data_0894CC1C[];
extern const u8 data_083A23C0[];
extern const u8 data_083A2334[];
extern const u8 data_083A23C8[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern u8 func_080DD580(void *);
extern u8 func_080DD670(void *, u8);
extern void func_080DF860(void *);
extern u8 func_080DBC18(void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080D6134(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_0810C244(void *task, Descriptor0810C244 *descriptor,
                  Payload0810C244 *payload)
{
    u8 animation;
    u16 output_mode;
    const void *record;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 3;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_task = func_080E03F8(payload->actor, data_083A2310,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        output_mode = 84;
        if (payload->mode != 0) {
            output_mode = 52;
            record = data_083A23B8;
        } else {
            record = data_083A23B0;
        }
        payload->record_task = func_080DFD8C(record, 1, 4, 0, task);
        payload->output_task = func_080DDF68(payload->actor, &payload->output,
            output_mode, 1, &payload->ready, data_083A23AC, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->resource_task = func_080D4B64(0, data_088F2BF0, 889, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->first_task = func_080D3E9C(data_0894D690, task);
        payload->second_task = func_080D4704(data_0894CC1C, task);
        payload->record_task = func_080DFD8C(data_083A23C0, 1, 4, 0, task);
        payload->countdown = 15;
        descriptor->phase++;
        break;
    case 0x102:
        if (--payload->countdown != 0)
            break;
        if (func_080DD580(payload->actor_object)) {
            if (func_080DD670(payload->actor_object, 8))
                func_080DF860(payload->coordinate_result);
            if (func_080DD670(payload->actor_object, 6))
                func_080DBC18(payload->coordinate_result, 15);
            payload->coordinate_task = func_080D6098(payload->x, payload->y,
                0, 1, 5, payload->unknown_20, data_083A2334, task);
            payload->record_task = func_080DFD8C(data_083A23C8, 2, 4, 36, task);
        } else {
            payload->object_task = func_080DCFE4(payload->actor_object, 0,
                12, 36, 4, task, 36);
        }
        descriptor->phase++;
        break;
    case 0x103:
        if (func_080DE1F0(payload->output) == 0)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->resource_task = func_080D4D2C(payload->resource_task, 0);
        if (payload->resource_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->first_task = func_080D3F08(payload->first_task);
        if (payload->first_task != 0)
            break;
        payload->second_task = func_080D4774(payload->second_task);
        if (payload->second_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
