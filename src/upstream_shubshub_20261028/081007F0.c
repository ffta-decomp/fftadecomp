/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081007F0.c
 * Original SHA-256: b07cbba4611335f0870629284bf6552bab0cc0e1cc0ac67494df7eb41aa5c30e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target [0x081007F0, 0x081009A6), 438 bytes including literal pools. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor081007F0;

/* Offset view only; the helper storage at +0x1c has no recovered type. */
typedef struct {
    u16 countdown;
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    void *output;
    void *coordinate_result;
    u32 unknown_10;
    void *actor;
    void *initial_child;
    u8 unknown_1c[0x10];
    void *coordinate_child;
    void *resource_child;
    void *effect_child;
    void *output_child;
    void *record_child;
} Payload081007F0;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_0839E8B8[];
extern const u8 data_0839E950[];
extern const u8 data_0839E8DC[];
extern const u8 data_0894848C[];
extern const u8 data_0839E93C[];
extern const u8 data_0839E954[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_081007F0(void *task, Descriptor081007F0 *descriptor,
                  Payload081007F0 *payload)
{
    void *actor;
    void *actor_object;
    u8 animation;
    u8 actor_status;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 3;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_0839E8B8,
                                               animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        actor_status = func_080D3B54(payload->actor);
        if (actor_status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->output_child = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready,
            data_0839E950, 5, actor_status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DC12C(payload->actor, 0, 0);
        payload->countdown = 20;
        descriptor->phase++;
        /* Fall through: begin the countdown in this invocation. */
    case 0x102:
        if (payload->countdown != 0 && --payload->countdown != 0)
            break;
        if (func_080D8B4C() != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 4, payload->unknown_1c, data_0839E8DC, task);
        payload->resource_child = func_080D4704(data_0894848C, task);
        payload->effect_child = func_080DCFE4(actor_object, data_0839E93C,
            12, 50, 20, task, 50);
        payload->record_child = func_080DFD8C(data_0839E954, 3, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (func_080DE1F0(payload->output) == 0)
            break;
        payload->resource_child = func_080D4774(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
