/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080DE61C.c
 * Original SHA-256: d3656b8da0800ca36eefabe6a770a86ace15bc816734da3b6074d0baa2300989
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    void *unit;
    u8 unknown_04[4];
    s16 x, y, z;
} Actor;
typedef struct {
    u16 phase;
    u16 unknown_02;
    Actor *actor;
    u8 unknown_08[12];
    u16 delay;
    u16 mode;
} Descriptor;
typedef struct {
    u16 cooldown;
    u16 delay;
    u8 mode;
    u8 unknown_05[3];
    Actor *actor;
    void *task;
    void *object;
} Payload;

extern const u16 data_083955F0[];
extern const void *const data_083955E0[];
extern const u8 data_083955EC[];
extern const u8 data_08500EC0[];
extern u16 func_080DD708(const void *);
extern u16 func_080DD6F4(const void *);
extern void *func_080DD478(const void *);
extern u8 func_080CDCD4(const void *);
extern void func_080DE10C(void *, u16);
extern void *func_080DE0E0(void *, const void *, u8, u32, void *);
extern s32 func_080C7EA4(const void *, u32);
extern void func_080DF640(void *, u8);
extern u8 func_080C8384(const void *);
extern u8 func_080D39B0(void);
extern u32 func_080D5E80(const void *, u16, s16, s16, s16, u16, u8);
extern void func_08011058(void *, s16);
extern void *func_080DBA5C(void *);
extern void *func_08011484(void *);

static inline u8 special_kind(u16 value)
{
    switch (value) {
    case 99: case 100: case 109: case 110: case 111:
        return 1;
    }
    return 0;
}

static inline u8 normal_kind(u16 value)
{
    if (value == 8 || value == 15)
        return 0;
    return 1;
}

u32 func_080DE61C(void *task, Descriptor *descriptor, Payload *payload)
{
    u8 kind;
    void *unit;
    u16 first, second;
    s16 x, y, z;

    switch (descriptor->phase) {
    case 0:
        payload->actor = descriptor->actor;
        payload->delay = descriptor->delay + 1;
        payload->mode = descriptor->mode;
        break;
    case 0x100:
        if (--payload->delay)
            break;
        kind = 0;
        if (special_kind(func_080DD708(payload->actor)))
            kind = 2;
        else if (!normal_kind(func_080DD6F4(payload->actor)))
            kind = 1;
        unit = func_080DD478(payload->actor);
        if (func_080CDCD4(unit)) {
            func_080DE10C(payload->actor, data_083955F0[kind]);
            payload->delay = 1;
            descriptor->phase = 0x102;
            break;
        }
        payload->task = func_080DE0E0(payload->actor, data_083955E0[kind],
                                      data_083955EC[kind], 0, task);
        first = func_080C7EA4(unit, 3);
        second = func_080C7EA4(unit, 4);
        payload->delay = 1;
        if (first == 21 && second == 99)
            payload->delay = 43;
        payload->cooldown = 4;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->delay && --payload->delay == 0 && payload->mode != 255)
            func_080DF640(payload->actor, payload->mode);
        if (func_080C8384(payload->actor->unit)) {
            if (payload->cooldown && --payload->cooldown)
                break;
            if (!func_080D39B0())
                break;
            func_080DBD5C((Struct080DBD5C *)payload->actor, &x, &y, &z);
            payload->object = (void *)func_080D5E80(data_08500EC0, 0,
                                                       x, y, z, 0x24C, 2);
            func_08011058(payload->object, -1);
        }
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->delay) {
            if (--payload->delay)
                break;
            if (payload->mode != 255)
                func_080DF640(payload->actor, payload->mode);
        }
        payload->task = func_080DBA5C(payload->task);
        if (payload->task)
            break;
        payload->object = func_08011484(payload->object);
        if (!payload->object)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
