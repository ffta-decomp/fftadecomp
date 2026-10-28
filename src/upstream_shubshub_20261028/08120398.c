/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08120398.c
 * Original SHA-256: 06849b3671c3ce3831617d214ebf9f2e308c3fe54e9e7b4730b287a416789ae4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08120398, 0x081204A8): 272 bytes, 121 instructions. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void **output;
    u8 unknown_08[0xC];
    u16 category;
    u16 variant;
    u8 delay;
} ObjectScript;

typedef struct {
    u16 flags;
    u8 unknown_02[6];
    u8 category;
    u8 variant;
    u8 unknown_0a;
    u8 delay;
    void **output;
    void *effect;
} ObjectPayload;

typedef struct {
    u8 first_id;
    u8 second_id;
    s16 x;
    s16 y;
    u16 unknown_06;
} ObjectEntry;

extern const ObjectEntry data_083A796C[][4];
extern const u8 data_08509094[];
extern const u8 data_0850939C[];
extern void *func_080D5CC0(const void *, u32, s16, s16, u32, u32, u32, u32);
extern void func_08011100(void *, u32);
extern void *func_08011484(void *);

u32 func_08120398(void *object, ObjectScript *script, ObjectPayload *payload)
{
    const ObjectEntry *entry;

    if (payload->flags & 0x8000)
        return 0;

    switch (script->state) {
    case 0:
        payload->category = script->category;
        payload->variant = script->variant;
        payload->delay = script->delay + 1;
        payload->output = script->output;
        break;
    case 0x100:
        if (--payload->delay != 0)
            break;
        entry = &data_083A796C[payload->category][payload->variant];
        *payload->output = func_080D5CC0(data_08509094, entry->first_id,
            entry->x + 64, entry->y, 397, 6, 1, 0);
        payload->effect = func_080D5CC0(data_0850939C, entry->second_id + 1,
            entry->x + 64, entry->y, 310, 6, 1, 0);
        func_08011100(payload->effect, 2);
        script->state++;
        break;
    case 0x101:
        payload->effect = func_08011484(payload->effect);
        if (payload->effect == 0)
            script->state++;
        break;
    case 0x102:
        script->state = 2;
        break;
    }
    return 0;
}
