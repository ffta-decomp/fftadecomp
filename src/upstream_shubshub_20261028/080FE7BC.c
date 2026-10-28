/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FE7BC.c
 * Original SHA-256: ff0479a74703e32e75187a58367a3c112d9308a0c5131f80a2eb9e33d2eb0ef7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080FE7BC, 0x080FE91E), 354 bytes, 149 instructions. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080FE7BC;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04;
    u8 flag;
    u8 ready;
    u8 unknown_07;
    void *output;
    u32 coordinate_result;
    void *actor;
    void *initial_task;
    u8 unknown_18[12];
    void *coordinate_task;
    void *effect_task;
    void *output_task;
    void *sound_task;
} Payload080FE7BC;

extern const u8 data_0839DC84[];
extern const u8 data_0839DD10[];
extern const u8 data_0839DCB4[];
extern const u8 data_0839DCFC[];
extern const u8 data_0839DD18[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE1F0(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FE7BC(void *task, Descriptor080FE7BC *descriptor,
                  Payload080FE7BC *payload)
{
    void *actor;
    void *object;
    u8 mode;
    u8 actor_status;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_0839DC84,
            mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        actor_status = func_080D3B54(payload->actor);
        if (actor_status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->output_task = func_080DDF68(payload->actor,
            &payload->output, 52, 2, &payload->ready, data_0839DD10,
            0, actor_status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_18, data_0839DCB4, task);
        payload->effect_task = func_080DCFE4(object, data_0839DCFC,
            12, 25, 4, task, 25);
        payload->sound_task = func_080DFD8C(data_0839DD18, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (func_080DE1F0(payload->output) == 0)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
