/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081064A4.c
 * Original SHA-256: 3778f03a3d59c66caf381775aabd50aaf8d1b5f6be80d42884ff88470e7896f4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x081064A4, complete [0x081064A4, 0x081065B2), 270 bytes. */

/* Local offset views; original declaration extents remain unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0e];
    u16 flag;
} Descriptor081064A4;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *coordinate_result;
    u8 unknown_0c[0x0c];
    void *position_child;
    void *initial_child;
    void *actor;
    void *effect_child;
    void *output_child;
} Payload081064A4;

extern const u8 data_083A03C0[];
extern const u8 data_083A03E4[];
extern const u8 data_083A042C[];
extern const u8 data_083A0440[];
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_081064A4(void *task, Descriptor081064A4 *descriptor,
                  Payload081064A4 *payload)
{
    void *actor;
    void *actor_object;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 3;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_083A03C0,
                                              animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        payload->position_child = func_080D6098(payload->x, payload->y, 0, 1,
            3, payload->unknown_0c, data_083A03E4, task);
        payload->effect_child = func_080DCFE4(actor_object, data_083A042C,
            12, 80, 4, task, 80);
        payload->output_child = func_080DFD8C(data_083A0440, 3, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
