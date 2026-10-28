/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08101CCC.c
 * Original SHA-256: 82cb2fc8c25c2c0e1257d3be08f1370bce88fa4b52b7caef5586485cfe0eb503
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08101CCC, 0x08101E1A), 334 bytes, 143 instructions.
 * Offset views only; unknown storage spans do not recover original declarations
 * or object extents. Helper returns, storage effects and ABI preservation remain
 * opaque; later phase/status/handle validity is a separate premise. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor08101CCC;

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
    void *coordinate_task;
    u8 unknown_1c[8];
    void *actor;
    void *initial_task;
    void *object_task;
    void *sound_task;
} Payload08101CCC;

/* These names bind observed addresses only; their original extents are unknown. */
extern const u8 data_0839EDC8[];
extern const u8 data_0839EDEC[];
extern const u8 data_0839EE1C[];
extern const u8 data_0839EE30[];

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

u32 func_08101CCC(void *task, Descriptor08101CCC *descriptor,
                  Payload08101CCC *payload)
{
    void *actor;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 3;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_0839EDC8,
            mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        payload->request_task = func_08102B48(payload->actor, 3,
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
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_1c, data_0839EDEC, task);
        payload->object_task = func_080DCFE4(payload->object, data_0839EE1C,
            12, 27, 4, task, 27);
        payload->sound_task = func_080DFD8C(data_0839EE30, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
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
