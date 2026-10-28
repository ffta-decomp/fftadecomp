/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0811A488.c
 * Original SHA-256: 79e8bd9978e7d01c3d4ed006ddc75d8c45b47e85a60295d14cfd0afb555f079d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0811A488, 0x0811A66A), 482 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *input;
    u16 unknown_08[7];
    u16 mode;
} Descriptor0811A488;

typedef struct {
    u16 delay;
    u8 mode;
    u8 unknown_03;
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_0a;
    void *object;
    void *coordinate_result;
    void *effects[3];
    void *initial_task;
    void *input;
    void *object_task;
    void *record_task;
} Payload0811A488;

extern const u8 data_083A6650[];
extern const u8 data_084F6130[];
extern const u8 data_083A6688[];
extern const u8 data_084FE8B0[];
extern const u8 data_083A6690[];
extern const u8 data_083A6674[];
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD73C(void *);
extern void *func_080D5E80(const void *, u16, s16, s16, s16, s16, u8);
extern void func_08011058(void *, s32);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD580(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080D5F24(void **, u16);
extern void *func_080DBA5C(void *);

u32 func_0811A488(void *task, Descriptor0811A488 *descriptor,
                  Payload0811A488 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;

            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 3;
            if (payload->mode)
                mode = 0;
            payload->initial_task = func_080E03F8(payload->input,
                data_083A6650, mode, 1, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (!func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD4A4(payload->input, 0);
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, &payload->z);
        if (func_080DD73C(payload->coordinate_result))
            payload->y += 16;
        payload->effects[0] = func_080D5E80(data_084F6130, 10,
            payload->x, payload->y, payload->z, 900, 7);
        payload->effects[1] = func_080D5E80(data_084F6130, 9,
            payload->x, payload->y, payload->z, 900, 7);
        func_08011058(payload->effects[0], -1);
        func_08011058(payload->effects[1], 1);
        payload->record_task = func_080DFD8C(data_083A6688, 1, 4, 0, task);
        payload->delay = 30;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->delay) {
            payload->delay--;
            break;
        }
        if (func_080DD580(payload->object)) {
            payload->effects[2] = func_080D5E80(data_084FE8B0, 0,
                payload->x, payload->y, payload->z, 996, 6);
            func_08011058(payload->effects[2], -2);
            payload->record_task = func_080DFD8C(data_083A6690,
                1, 4, 0, task);
        }
        payload->object_task = func_080DCFE4(payload->object, data_083A6674,
            12, 0, 2, task, 0);
        descriptor->phase++;
        break;
    case 0x102:
        if (func_080D5F24(payload->effects, 3)) {
            payload->object_task = func_080DBA5C(payload->object_task);
            if (payload->object_task == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
