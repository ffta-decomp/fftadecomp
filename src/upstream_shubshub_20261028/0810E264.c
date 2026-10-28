/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810E264.c
 * Original SHA-256: 06696184d81b9f6630414a59a1004dcb972d15a5e842036f7333ec2a0fd0b139
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810E264, 0x0810E44C), 488 bytes, 196 instructions.
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
} Descriptor0810E264;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 mode;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *actor_object;
    u8 unknown_10[0x20];
    void *coordinate_task;
    void *resource_task;
    void *first_task;
    void *second_task;
    void *output_task;
    void *initial_task;
    void *actor;
    void *object_task;
    void *record_task;
} Payload0810E264;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A2A38[];
extern const u8 data_088F2DFC[];
extern u16 g_control_flags_03000940;
extern const u8 data_0894D69C[];
extern const u8 data_0894CEC0[];
extern const u8 data_08948684[];
extern const u8 data_083A2A68[];
extern const u8 data_083A2B50[];
extern const u8 data_083A2B28[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern s8 func_080DD5A8(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810E264(void *task, Descriptor0810E264 *descriptor,
                  Payload0810E264 *payload)
{
    u8 animation;
    u32 alternate;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 4;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_task = func_080E03F8(payload->actor, data_083A2A38,
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
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->resource_task = func_080D4B64(0, data_088F2DFC, 881, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->output_task = func_080D3E9C(data_0894D69C, task);
        payload->first_task = func_080D4704(data_0894CEC0, task);
        payload->second_task = func_080D4724(data_08948684, task, 60);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 8, payload->unknown_10, data_083A2A68, task);
        payload->record_task = func_080DFD8C(data_083A2B50, 1, 4, 0, task);
        alternate = func_080DD5A8(payload->actor_object) != 0;
        payload->object_task = func_080DCFE4(payload->actor_object,
            data_083A2B28 + 20 * alternate, 12, 90, 12, task, 90);
        descriptor->phase++;
        break;
    case 0x101:
        payload->output_task = func_080D3F08(payload->output_task);
        if (payload->output_task != 0)
            break;
        payload->resource_task = func_080D4D2C(payload->resource_task, 0);
        if (payload->resource_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->first_task = func_080D4774(payload->first_task);
        if (payload->first_task != 0)
            break;
        payload->second_task = func_080D4774(payload->second_task);
        if (payload->second_task != 0)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
