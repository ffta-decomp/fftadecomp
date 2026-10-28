/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810D590.c
 * Original SHA-256: a5f2a632c1f2bc1abc723270b270570d66fdbe08ff8a898848e41575ef6ab78e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810D590, 0x0810D726), 406 bytes, 167 instructions.
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
} Descriptor0810D590;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 flag;
    u8 mode;
    void *coordinate_result;
    void *actor_object;
    u32 coordinate_output;
    void *coordinate_task;
    void *first_task;
    void *second_task;
    void *object_task;
    void *actor;
    void *initial_task;
    void *record_task;
} Payload0810D590;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A275C[];
extern const u8 data_088F58BC[];
extern const u8 data_0894CCC0[];
extern const u8 data_0894D69C[];
extern const u8 data_083A278C[];
extern const u8 data_083A27A4[];
extern const u8 data_083A27B8[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(u8);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810D590(void *task, Descriptor0810D590 *descriptor,
                  Payload0810D590 *payload)
{
    u8 animation;
    void *initial_task;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 4;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_task = func_080E03F8(payload->actor, data_083A275C,
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
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        func_080D7220(data_088F58BC, 0, 2, payload->x,
            (s16)(payload->y - 4), (u32)initial_task);
        payload->first_task = func_080D4704(data_0894CCC0, task);
        payload->second_task = func_080D3E9C(data_0894D69C, task);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 1, &payload->coordinate_output, data_083A278C, task);
        payload->object_task = func_080DCFE4(payload->actor_object,
            data_083A27A4, 12, 80, 4, task, 80);
        payload->record_task = func_080DFD8C(data_083A27B8, 2, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->first_task = func_080D4774(payload->first_task);
        if (payload->first_task != 0)
            break;
        payload->second_task = func_080D3F08(payload->second_task);
        if (payload->second_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        descriptor->phase++;
        break;
    case 0x102:
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
