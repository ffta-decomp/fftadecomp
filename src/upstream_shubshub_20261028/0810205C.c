/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810205C.c
 * Original SHA-256: 5b88f4da0d2f18ff6ddc210e4a6f9fa38452ed728945b7316792577f3ba860fc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810205C, 0x081021E6), 394 bytes, 167 instructions.
 * Offset views only; unknown storage spans do not recover original declarations
 * or object extents. Helper returns, storage effects and ABI preservation remain
 * opaque; later phase/status/handle validity is a separate premise. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor0810205C;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 ready;
    s16 x;
    s16 y;
    void *request_task;
    void *actor_result;
    u32 coordinate_result;
    void *object;
    void *first_coordinate_task;
    u8 unknown_1c[8];
    void *second_coordinate_task;
    u8 unknown_28[4];
    void *actor;
    void *initial_task;
    void *object_task;
    void *sound_task;
} Payload0810205C;

/* These names bind observed addresses only; their original extents are unknown. */
extern const u8 data_0839EEE4[];
extern const u8 data_0839EF14[];
extern const u8 data_0839EF44[];
extern const u8 data_0839EF5C[];
extern const u8 data_0839EF70[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_08102B48(void *, u8, u8 *, void *);
extern void *func_080DD47C(void *);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_08102BA8(void *);
extern void *func_080DBA5C(void *);

u32 func_0810205C(void *task, Descriptor0810205C *descriptor,
                  Payload0810205C *payload)
{
    void *actor;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_0839EEE4,
            mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        payload->request_task = func_08102B48(payload->actor, 5,
            &payload->ready, task);
        if (payload->request_task == 0)
            descriptor->phase = 2;
        else
            descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (payload->ready == 2) {
            descriptor->phase = 0x103;
            break;
        }
        payload->actor_result = func_080DD47C(payload->actor);
        payload->object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        descriptor->phase++;
        break;
    case 0x102:
        payload->first_coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_1c, data_0839EF14, task);
        payload->second_coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->unknown_28, data_0839EF44, task);
        payload->object_task = func_080DCFE4(payload->object, data_0839EF5C,
            12, 27, 4, task, 27);
        payload->sound_task = func_080DFD8C(data_0839EF70, 2, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        payload->first_coordinate_task = func_080D6134(payload->first_coordinate_task);
        if (payload->first_coordinate_task != 0)
            break;
        payload->second_coordinate_task = func_080D6134(payload->second_coordinate_task);
        if (payload->second_coordinate_task != 0)
            break;
        payload->request_task = func_08102BA8(payload->request_task);
        if (payload->request_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
