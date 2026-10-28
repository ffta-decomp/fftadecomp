/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810E09C.c
 * Original SHA-256: 955dfcc3225f4865667e3e4d33f2b7fb76bebc081a5129eea587f8e9d881499c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0810E09C, 0x0810E262), 454 bytes, 182 instructions.
 * Local offset views; original declarations and storage extents are unknown.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 variant;
} Descriptor0810E09C;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 mode;
    u8 variant;
    u32 unknown_08;
    void *coordinate_result;
    void *actor_object;
    void *actor;
    void *initial_child;
    u32 coordinate_output;
    void *coordinate_child;
    void *sprite;
    void *first_child;
    void *second_child;
    void *effect_child;
    void *record_child;
} Payload0810E09C;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A29B0[];
extern const u8 data_088F2BF0[];
extern const u8 data_0894D7E4[];
extern const u8 data_0894CC1C[];
extern const u8 data_083A29D4[];
extern const u8 data_083A2A00[];
extern const u8 data_083A29EC[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D6134(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_0810E09C(void *owner, Descriptor0810E09C *descriptor,
                  Payload0810E09C *payload)
{
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 3;
        if (payload->variant != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_child = func_080E03F8(payload->actor, data_083A29B0,
            animation, 0, 0, owner);
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
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->sprite = func_080D4B64(0, data_088F2BF0, 889, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->first_child = func_080D3E9C(data_0894D7E4, owner);
        payload->second_child = func_080D4704(data_0894CC1C, owner);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, &payload->coordinate_output, data_083A29D4, owner);
        payload->record_child = func_080DFD8C(data_083A2A00, 2, 4, 0, owner);
        payload->effect_child = func_080DCFE4(payload->actor_object,
            data_083A29EC, 12, 50, 4, owner, 50);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->first_child = func_080D3F08(payload->first_child);
        if (payload->first_child != 0)
            break;
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child != 0)
            break;
        descriptor->phase++;
        break;
    case 0x102:
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
