/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810B978.c
 * Original SHA-256: e1fb7d993540a0cca681003a4197d1e0b55814a50df662f640626c0cce78aab1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target [0x0810B978, 0x0810BB6E), 502 bytes.
 * Local offset views; original declaration types and extents are unknown. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 mode;
} Descriptor0810B978;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u8 source_mode;
    u8 first_ready;
    u8 second_ready;
    u8 unknown_09[3];
    void *object;
    void *coordinate_result;
    void *actor_object;
    void *actor;
    void *initial_child;
    u32 unknown_20[3];
    void *first_child;
    u32 unknown_30[3];
    void *second_child;
    void *object_child;
    void *animation_child;
    void *record_child;
} Payload0810B978;

extern const u8 data_083A20F0[];
extern const u8 data_083A21B8[];
extern const u8 data_083A2114[];
extern const u8 data_083A21C0[];
extern const u8 data_083A215C[];
extern const u8 data_083A21A4[];
extern const u8 data_083A21C8[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD73C(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE244(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810B978(void *task, Descriptor0810B978 *descriptor,
                  Payload0810B978 *payload)
{
    u8 mode;
    u16 animation;

    switch (descriptor->phase) {
    case 0:
        payload->source_mode = descriptor->mode;
        payload->actor = descriptor->actor;
        mode = 3;
        if (payload->source_mode != 0)
            mode = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_child = func_080E03F8(payload->actor,
            data_083A20F0, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        animation = 88;
        if (payload->mode != 0)
            animation = 52;
        payload->animation_child = func_080DDF68(payload->actor,
            &payload->object, animation, 2, &payload->first_ready,
            data_083A21B8, 0, 0, task);
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        if (func_080DD73C(payload->coordinate_result))
            payload->y -= 8;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->first_child == 0 && payload->first_ready != 0) {
            payload->first_child = func_080D6098(payload->x, payload->y,
                0, 1, 3, payload->unknown_20, data_083A2114, task);
            payload->record_child = func_080DFD8C(data_083A21C0,
                1, 4, 0, task);
        }
        if (payload->second_child == 0 && payload->second_ready != 0) {
            payload->second_child = func_080D6098(payload->x, payload->y,
                0, 1, 3, payload->unknown_30, data_083A215C, task);
            payload->object_child = func_080DCFE4(payload->actor_object,
                data_083A21A4, 12, 30, 12, task, 30);
            payload->record_child = func_080DFD8C(data_083A21C8,
                1, 4, 0, task);
        }
        if (payload->first_child != 0 && payload->second_child != 0)
            descriptor->phase++;
        break;
    case 0x102:
        if (func_080DE244(payload->object) == 0)
            break;
        payload->first_child = func_080D6134(payload->first_child);
        if (payload->first_child != 0)
            break;
        payload->second_child = func_080D6134(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
