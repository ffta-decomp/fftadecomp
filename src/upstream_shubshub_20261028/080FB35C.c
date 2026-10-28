/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FB35C.c
 * Original SHA-256: 5064566d77791996d3fc1a2dbc842564c6ebc4a9503af9f37428f2d942a02a91
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080FB35C..0x080FB4B8 — 348 bytes, including literal pools. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0c];
    s16 id;
    u16 flag;
} Descriptor080FB35C;

typedef struct {
    u16 unknown_00;
    u8 variant;
    u8 flag;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *effect;
    void *sequence;
    void *animation;
    void *actor;
    u32 unknown_1c;
    void *auxiliary;
} Payload080FB35C;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD760(void *, s16 *, s16 *, u32, s16);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u16 func_080035A8(u8);

extern const u8 data_0839CC7C[];
extern const void *const data_0839CC74[];
extern const void *const data_0839CC80[];

u32 func_080FB35C(void *task, Descriptor080FB35C *descriptor,
                  Payload080FB35C *payload)
{
    void *actor;
    void *handle;
    u8 animation;
    s16 offset;

    switch (descriptor->phase) {
    case 0:
        payload->variant = 0;
        if (descriptor->id == 0x85)
            payload->variant = 1;
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = data_0839CC7C[payload->variant];
        if (payload->flag != 0)
            animation = 0;
        payload->animation = func_080E03F8(
            actor, data_0839CC74[payload->variant],
            animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->animation = func_080E05DC(payload->animation);
        if (payload->animation != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        handle = func_080DD4A4(payload->actor, 0);
        offset = 36;
        if (payload->variant == 1)
            offset = -2;
        payload->coordinate_result = func_080DD760(
            handle, &payload->x, &payload->y, 0, offset);
        func_080D7220(data_0839CC80[payload->variant],
                      0, 2, payload->x, payload->y, 0);
        payload->effect = func_080D4704((const void *)0x0894A6E8, task);
        payload->sequence = func_080D3E9C((const void *)0x0894D9F4, task);
        payload->auxiliary = func_080DFD8C((const void *)0x0839CC88,
                                         2, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->sequence = func_080D3F08(payload->sequence);
        if (payload->sequence != 0)
            break;
        payload->effect = func_080D4774(payload->effect);
        if (payload->effect != 0)
            break;
        *(u16 *)0x03000940 &= ~func_080035A8(2);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
