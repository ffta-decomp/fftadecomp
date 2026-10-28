/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810482C.c
 * Original SHA-256: 31c2aa885fa28f9fec334f5ae527cce68c565eef4b86c8cad8d8e8fb47c0c49e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810482C, 0x0810493A), 270 bytes, 114 instructions. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor0810482C;

typedef struct {
    u8 flag;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    u32 coordinate_result;
    u8 unknown_0c[8];
    void *coordinate_task;
    void *initial_task;
    void *actor;
    void *object_task;
    void *sound_task;
} Payload0810482C;

extern const u8 data_0839F690[];
extern const u8 data_0839F6B4[];
extern const u8 data_0839F6E4[];
extern const u8 data_0839F6F8[];

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

u32 func_0810482C(void *task, Descriptor0810482C *descriptor,
                  Payload0810482C *payload)
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
        payload->initial_task = func_080E03F8(actor, data_0839F690,
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
            0, 1, 2, payload->unknown_0c, data_0839F6B4, task);
        payload->object_task = func_080DCFE4(object, data_0839F6E4,
            12, 100, 12, task, 100);
        payload->sound_task = func_080DFD8C(data_0839F6F8, 2, 4, 0, task);
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
