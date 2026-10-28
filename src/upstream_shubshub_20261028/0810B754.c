/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810B754.c
 * Original SHA-256: 85a46fc2ad6d1016d6feefaf4affffa1f822daf20a7ac2474937ae0898304eb6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0810B754 .. 0x0810B976: 546 bytes.
 * Local offset views; unknown members and asset extents are not recovered. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 variant;
} Descriptor0810B754;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 variant;
    u8 mode;
    u8 signal;
    u8 unknown_09[3];
    void *target;
    void *position_result;
    void *actor_part;
    void *actor;
    u32 initial_handle;
    u32 first_output;
    u8 unknown_24[8];
    u32 first_handle;
    u32 second_output;
    u32 second_handle;
    u32 effect_handle;
    u32 setup_handle;
    u32 record_handle;
} Payload0810B754;

extern const u8 data_083A2000[];
extern const u8 data_083A20B0[];
extern const u8 data_083A203C[];
extern const u8 data_083A20B8[];
extern const u8 data_083A2084[];
extern const u8 data_083A20C0[];
extern const u8 data_083A209C[];

extern u32 func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32);
extern u8 func_080D3B54(void *);
extern u32 func_080DDF68(void *, void **, u32, u32, u8 *, const void *, u32, u32, void *);
extern u8 func_080D8858(void *, u8);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern s8 func_080DBC88(void *);
extern u32 func_080D6098(s16, s16, s16, u8, u16, u32 *, const void *, void *);
extern void func_080D6194(u32, u8);
extern u32 func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD580(void *);
extern u8 func_080DD670(void *, u8);
extern u32 func_080DCFE4(void *, const void *, u16, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern u32 func_080D6134(u32);
extern u32 func_080DBA5C(u32);

u32 func_0810B754(void *owner, Descriptor0810B754 *descriptor,
                  Payload0810B754 *payload)
{
    u8 kind;
    u8 target_variant;
    u32 setup_kind;
    u16 duration;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        kind = 5;
        if (payload->variant != 0)
            kind = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_handle = func_080E03F8(payload->actor, data_083A2000,
                                               kind, 0, 0, owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_handle = func_080E05DC(payload->initial_handle);
        if (payload->initial_handle != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        setup_kind = 84;
        if (payload->mode)
            setup_kind = 52;
        payload->setup_handle = func_080DDF68(payload->actor, &payload->target,
                                              setup_kind, 2, &payload->signal,
                                              data_083A20B0, 3, 0, owner);
        payload->countdown = 10;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->signal) {
            payload->countdown = 10;
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        if (!func_080D8858(payload->actor, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_part = func_080DD4A4(payload->actor, 0);
        payload->position_result = func_080DD748(payload->actor_part,
                                                &payload->x, &payload->y, 0);
        target_variant = func_080DBC88(payload->target);
        payload->first_handle = func_080D6098(payload->x, payload->y, 0, 1,
                                              3, &payload->first_output,
                                              data_083A203C, owner);
        if (target_variant > 1)
            func_080D6194(payload->first_handle, 1);
        payload->record_handle = func_080DFD8C(data_083A20B8, 1, 4, 0, owner);
        duration = 30;
        if (func_080DD580(payload->actor_part) &&
            func_080DD670(payload->actor_part, 9)) {
            duration = 80;
            payload->second_handle = func_080D6098(payload->x, payload->y, 0, 1,
                                                   1, &payload->second_output,
                                                   data_083A2084, owner);
            payload->record_handle = func_080DFD8C(data_083A20C0, 1, 4, 30, owner);
        }
        payload->effect_handle = func_080DCFE4(payload->actor_part, data_083A209C,
                                               12, duration, 4, owner, duration);
        descriptor->phase++;
        break;
    case 0x103:
        if (!func_080DE1F0(payload->target))
            break;
        payload->first_handle = func_080D6134(payload->first_handle);
        if (payload->first_handle != 0)
            break;
        payload->second_handle = func_080D6134(payload->second_handle);
        if (payload->second_handle != 0)
            break;
        payload->effect_handle = func_080DBA5C(payload->effect_handle);
        if (payload->effect_handle == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
