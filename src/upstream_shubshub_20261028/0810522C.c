/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810522C.c
 * Original SHA-256: 5ca78e5bc9a44533d2bc5f3d4238ede983ede21d8ede1545e4ab7a8a71d486a4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810522C, 0x0810533A), 270 bytes, 114 instructions.
 * These offset views do not recover original declarations or object extents.
 * Helper returns, storage effects and ABI preservation remain opaque; later
 * phases and valid handles are independent premises. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor0810522C;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    u32 coordinate_result;
    u8 unknown_0c[28];
    void *coordinate_task;
    void *initial_task;
    void *actor;
    void *object_task;
    void *sound_task;
} Payload0810522C;

/* Observed address bindings only; original asset extents are unknown. */
extern const u8 data_0839F8C0[];
extern const u8 data_0839F8E4[];
extern const u8 data_0839F98C[];
extern const u8 data_0839F9A0[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810522C(void *task, Descriptor0810522C *descriptor,
                  Payload0810522C *payload)
{
    void *actor;
    void *object;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 3;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_0839F8C0,
            mode, 1, 0, task);
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
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 7, payload->unknown_0c, data_0839F8E4, task);
        payload->object_task = func_080DCFE4(object, data_0839F98C,
            12, 110, 12, task, 110);
        payload->sound_task = func_080DFD8C(data_0839F9A0, 2, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
