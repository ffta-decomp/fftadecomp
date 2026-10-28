/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081072B0.c
 * Original SHA-256: a60ec6822e43e0283892134188ad2b2f0815be61e14eb857236a861a7d669703
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x081072B0, complete [0x081072B0, 0x081074D8), 552 bytes:
 * 498 code bytes, 48 literal bytes and six internal alignment bytes. */

/* Local access views; original declaration types and extents are unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 variant;
} Descriptor081072B0;

typedef struct {
    u16 field_00;
    u8 mode;
    u8 variant;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *actor_object;
    u32 first_output;
    void *first_child;
    u32 second_output;
    u32 unknown_1c;
    void *second_child;
    void *sprite;
    void *resource_child;
    void *initial_child;
    void *actor;
    void *effect_child;
    void *record_child;
} Payload081072B0;

extern const u8 data_083A0BB4[];
extern const u8 data_088F1670[];
extern const u8 data_0894D69C[];
extern const u8 data_083A0C4C[];
extern const u8 data_083A0BF0[];
extern const u8 data_083A0C08[];
extern const u8 data_083A0C54[];
extern const u8 data_083A0C38[];
extern u16 g_control_flags_03000940;

/* Prototypes describe the argument values used at these call sites. */
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DF8B0(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D620C(void *, s16);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);
extern void func_080D4D14(void *, u8);

u32 func_081072B0(void *task, Descriptor081072B0 *descriptor,
                  Payload081072B0 *payload)
{
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 5;
        if (payload->variant != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_child = func_080E03F8(payload->actor, data_083A0BB4,
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
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        if (func_080DF8B0(payload->coordinate_result)) {
            payload->x -= 4;
            payload->y += 20;
        }
        func_080D49FC(0, 2, 0, (s16)(payload->x + 20),
            (s16)(payload->y - 36));
        payload->sprite = func_080D4B64(0, data_088F1670, 973, 7);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->resource_child = func_080D3E9C(data_0894D69C, task);
        payload->record_child = func_080DFD8C(data_083A0C4C, 1, 4, 0, task);
        payload->field_00 = 12;
        descriptor->phase++;
        break;
    case 0x101:
        payload->first_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, &payload->first_output, data_083A0BF0, task);
        payload->second_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, &payload->second_output, data_083A0C08, task);
        func_080D620C(payload->second_child, -1);
        payload->record_child = func_080DFD8C(data_083A0C54, 1, 4, 48, task);
        payload->effect_child = func_080DCFE4(payload->actor_object,
            data_083A0C38, 12, 68, 4, task, 68);
        descriptor->phase++;
        break;
    case 0x102:
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite != 0)
            break;
        payload->resource_child = func_080D3F08(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->first_child = func_080D6134(payload->first_child);
        if (payload->first_child != 0)
            break;
        payload->second_child = func_080D6134(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        func_080D4D14(payload->sprite, 0);
        payload->sprite = 0;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
