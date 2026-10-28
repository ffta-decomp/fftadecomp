/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810D34C.c
 * Original SHA-256: b71ddfe0212dcd6cb5aad6291a71cf3298782daf7b400e0513cdcf7e2e2042c3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x0810D34C .. 0x0810D46E: 290 bytes, including literal pools.
 * Local access views; original declaration types and extents are unknown.
 * Helper returns, storage validity/lifetime and returning ABI remain premises. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    u16 mode;
} Descriptor0810D34C;

typedef struct {
    u16 unknown_00;
    u8 mode;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *actor;
    void *position;
    void *sprite;
    void *child;
    void *actor_effect;
    void *record;
} Payload0810D34C;

extern const u8 data_088F2D60[];
extern const u8 data_0894DE24[];
extern const u8 data_083A2718[];
extern const u8 data_083A272C[];
extern u16 g_control_flags_03000940;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080DBA5C(void *);

u32 func_0810D34C(void *owner, Descriptor0810D34C *descriptor,
                  Payload0810D34C *payload)
{
    switch (descriptor->phase) {
    case 0: {
        void *actor;
        payload->mode = descriptor->mode;
        actor = descriptor->actor;
        payload->actor = actor;
        payload->position = func_080DD748(actor, &payload->x,
                                         &payload->y, 0);
        break;
    }
    case 0x100:
        func_080D49FC(0, 2, 0, payload->x, (s16)(payload->y - 32));
        payload->sprite = func_080D4B64(0, data_088F2D60, 965, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->child = func_080D3E9C(data_0894DE24, owner);
        payload->actor_effect = func_080DCFE4(payload->actor, data_083A2718,
                                             12, 55, 10, owner, 55);
        payload->record = func_080DFD8C(data_083A272C, 1, 20, 0, owner);
        descriptor->phase++;
        break;
    case 0x101:
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite != 0)
            break;
        {
            u8 had_child = payload->child != 0;
            payload->child = func_080D3F08(payload->child);
            if (payload->child != 0)
                break;
            if (had_child) {
                u32 mask = func_080035A8(2);
                g_control_flags_03000940 &= ~mask;
            }
        }
        descriptor->phase++;
        break;
    case 0x102:
        payload->actor_effect = func_080DBA5C(payload->actor_effect);
        if (payload->actor_effect == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
