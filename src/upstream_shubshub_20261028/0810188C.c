/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810188C.c
 * Original SHA-256: 66f527bb084cd6803f262e3d0bb3eccbca87593312fd0a7f6ba08eb8b809899b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target [0x0810188C, 0x08101A8C): 512 bytes, 206 instructions.
 * These offset views cover the observed accesses, not original object extents.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 unknown_14;
    u16 flag;
} Descriptor0810188C;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 status;
    s16 x;
    s16 y;
    void *status_child;
    u32 unknown_0c;
    void *coordinate_result;
    void *selected_object;
    void *coordinate_child;
    u8 unknown_1c[16];
    void *resource;
    void *controller;
    void *first_child;
    void *second_child;
    void *actor;
    void *initial_child;
    u32 unknown_44;
    void *actor_child;
    void *record_child;
} Payload0810188C;

/* Address-only bindings; the forwarded data's original types/extents are unknown. */
extern const u8 data_0839EC80[];
extern const u8 data_0839ECB0[];
extern const u8 data_088F0A30[];
extern const u8 data_0894D5D0[];
extern const u8 data_0894AD80[];
extern const u8 data_0894848C[];
extern const u8 data_0839ECE0[];
extern const u8 data_0839ECF4[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_08102B48(void *, u8, u8 *, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D6134(void *);
extern void *func_08102BA8(void *);
extern void *func_080DBA5C(void *);

u32 func_0810188C(void *task, Descriptor0810188C *descriptor,
                  Payload0810188C *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        u8 mode;

        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->actor,
            data_0839EC80, mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        payload->status_child = func_08102B48(payload->actor, 1,
            &payload->status, task);
        if (payload->status_child == 0) {
            descriptor->phase = 2;
            break;
        }
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->status == 0)
            break;
        if (payload->status == 2) {
            descriptor->phase = 0x103;
            break;
        }
        payload->selected_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->selected_object,
            &payload->x, &payload->y, 0);
        descriptor->phase++;
        break;
    case 0x102:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_1c, data_0839ECB0, task);
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->resource = func_080D4B64(0, data_088F0A30, 919, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->controller = func_080D3E9C(data_0894D5D0, task);
        payload->first_child = func_080D4704(data_0894AD80, task);
        payload->second_child = func_080D4724(data_0894848C, task, 10);
        payload->actor_child = func_080DCFE4(payload->selected_object,
            data_0839ECE0, 12, 29, 4, task, 29);
        payload->record_child = func_080DFD8C(data_0839ECF4, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        payload->controller = func_080D3F08(payload->controller);
        if (payload->controller != 0)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child != 0)
            break;
        payload->resource = func_080D4D2C(payload->resource, 0);
        if (payload->resource != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->status_child = func_08102BA8(payload->status_child);
        if (payload->status_child != 0)
            break;
        payload->actor_child = func_080DBA5C(payload->actor_child);
        if (payload->actor_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
