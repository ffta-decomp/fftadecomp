/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FD358.c
 * Original SHA-256: a2d471b29b0e5f98c0d32900be3dd3dd174ee134107c8a60eb805ae44f62370e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: 0x080FD358..0x080FD496, complete 318-byte body. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 unknown_0C;
    u32 unknown_10;
    u16 unknown_14;
    u16 flag;
} Descriptor080FD358;

/* Offset view only; helper storage types and original extents are unknown. */
typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 status;
    u16 unknown_04;
    s16 x;
    s16 y;
    u16 unknown_0A;
    void *preparation_child;
    u32 unknown_10;
    void *coordinate_result;
    void *actor_state;
    u8 unknown_1C[0x10];
    void *coordinate_child;
    void *actor;
    void *initial_child;
    void *transition_child;
    void *retained_child;
} Payload080FD358;

struct Data080FD358;
extern const struct Data080FD358 data_0839D5C8;
extern const struct Data080FD358 data_0839D5E0;
extern const struct Data080FD358 data_0839D640;
extern const struct Data080FD358 data_0839D654;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080FDE58(void *, u8, u8, u8 *, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, s16, s16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080FDEBC(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FD358(void *task, Descriptor080FD358 *descriptor,
                  Payload080FD358 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;

        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 2;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->actor,
            &data_0839D5C8, mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        payload->preparation_child = func_080FDE58(payload->actor, 2, 0,
            &payload->status, task);
        if (payload->preparation_child == 0)
            descriptor->phase = 2;
        else
            descriptor->phase++;
        break;
    case 0x101:
        if (payload->status == 0)
            break;
        if (payload->status == 2) {
            descriptor->phase = 0x102;
            break;
        }
        payload->actor_state = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_state,
            &payload->x, &payload->y, 0);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 4, payload->unknown_1C, &data_0839D5E0, task);
        payload->transition_child = func_080DCFE4(payload->actor_state,
            &data_0839D640, 12, 62, 4, task, 62);
        payload->retained_child = func_080DFD8C(&data_0839D654, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->preparation_child = func_080FDEBC(payload->preparation_child);
        if (payload->preparation_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->transition_child = func_080DBA5C(payload->transition_child);
        if (payload->transition_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
