/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EDA00.c
 * Original SHA-256: df89dd9c7fe2cfca4de1410f33dd0058a353de7c9eafff8ad10378bd6a7783a1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0xC];
    u16 variant;
} Descriptor080EDA00;

typedef struct {
    u16 flags;
    u16 variant;
    u8 unknown_04[0x10];
} EffectSettings080EDA00;

typedef struct {
    u8 variant;
    u8 delay;
    u8 count;
    u8 index;
    void *actor;
    void *object;
    void *children[4];
    EffectSettings080EDA00 settings;
} Payload080EDA00;

typedef void (*CopyBuffer080EDA00)(void *destination, const void *source,
                                 u32 size);

extern CopyBuffer080EDA00 const data_0836D4BC[];
extern const EffectSettings080EDA00 data_083993D4;
extern const u8 data_083993CC[];
extern u8 func_080DD494(void *actor);
extern void *func_080DD4B4(void *actor, u8 index);
extern void func_080DB838(void *object);
extern u8 func_080D8B4C(void);
extern void *func_080DBA5C(void *child);
extern void *func_080DD4A4(void *actor, u8 index);
extern void *func_080DCFE4(void *object, const void *settings, u8 position,
                          u16 duration, u16 flags, void *task, u16 delay);

/* Complete [0x080EDA00, 0x080EDB80): 384 bytes, 173 instructions. */
u32 func_080EDA00(void *task, Descriptor080EDA00 *descriptor,
                  Payload080EDA00 *payload)
{
    u8 index;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        payload->count = func_080DD494(payload->actor);
        data_0836D4BC[0](&payload->settings, &data_083993D4,
                         sizeof(payload->settings));
        payload->settings.variant = data_083993CC[payload->variant];
        payload->object = func_080DD4B4(payload->actor, payload->index);
        func_080DB838(payload->object);
        break;
    case 1:
        break;
    case 0x100:
        if (func_080D8B4C())
            break;
        {
            void *object;
            void *child;
            s32 parity;
            u16 flags;

            for (index = 0; index < 4; index++)
                payload->children[index] = func_080DBA5C(payload->children[index]);
            object = func_080DD4A4(payload->actor, payload->index);
            parity = payload->index & 1;
            flags = 2;
            if (parity != 0)
                flags = 4;
            child = func_080DCFE4(object, &payload->settings,
                12 - (payload->index & 6), 10, flags | 8, task, 10);
            payload->children[payload->index & 3] = child;
        }
        payload->index++;
        if (payload->index == payload->count) {
            descriptor->phase = 0x103;
        } else {
            payload->delay = 30;
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (--payload->delay == 0) {
            payload->object = func_080DD4B4(payload->actor, payload->index);
            func_080DB838(payload->object);
            descriptor->phase = 0x100;
        }
        break;
    case 0x102:
        descriptor->phase++;
        break;
    case 0x103:
        {
            u8 done = 1;

            for (index = 0; index < 4; index++) {
                payload->children[index] = func_080DBA5C(payload->children[index]);
                if (payload->children[index] != 0)
                    done = 0;
            }
            if (done)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
