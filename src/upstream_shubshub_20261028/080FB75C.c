/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FB75C.c
 * Original SHA-256: 5b573c957821259631516c1111211bb775485302efc78eda87fda2db29ba8301
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 0x080FB75C..0x080FB918 (444 bytes). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    u16 unknown_14;
    u16 flag;
};

struct Payload {
    u16 unknown_00;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *actor_state;
    u32 unknown_10;
    u32 unknown_14;
    u32 unknown_18;
    void *sequence;
    void *effect;
    void *animation;
    void *initial;
    void *actor;
    void *transition;
    void *retained;
};

extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern void *func_080D4724(const void *, void *, int);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D6134(void *);
extern void *func_080DCFE4(void *, const void *, int, int, int, void *, int);
extern void *func_080D3F08(void *);
extern int func_080035A8(int);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

int func_080FB75C(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        int mode;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 6;
        if (payload->flag != 0)
            mode = 0;
        payload->initial = func_080E03F8(payload->actor, (const void *)0x0839CDD8,
                                       mode, 1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial = func_080E05DC(payload->initial);
        if (payload->initial != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_state = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_state,
                                                   &payload->x, &payload->y, 0);
        payload->sequence = func_080D6098(payload->x, payload->y, 0, 1, 2,
                                          &payload->unknown_10,
                                          (const void *)0x0839CE20, task);
        payload->effect = func_080D4724((const void *)0x0894ABA0, task, 30);
        func_080D7220((const void *)0x088F5A80, 0, 2, payload->x, payload->y, 0);
        payload->animation = func_080D3E9C((const void *)0x0894DA08, task);
        payload->retained = func_080DFD8C((const void *)0x0839CEAC, 3, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->sequence = func_080D6134(payload->sequence);
        if (payload->sequence != 0)
            break;
        payload->sequence = func_080D6098(payload->x, payload->y, 0, 1, 3,
                                          &payload->unknown_10,
                                          (const void *)0x0839CE50, task);
        payload->transition = func_080DCFE4(payload->actor_state,
                                           (const void *)0x0839CE98,
                                           12, 55, 4, task, 55);
        descriptor->phase++;
        break;
    case 0x102:
        payload->animation = func_080D3F08(payload->animation);
        if (payload->animation != 0)
            break;
        *(u16 *)0x03000940 &= ~func_080035A8(2);
        payload->sequence = func_080D6134(payload->sequence);
        if (payload->sequence != 0)
            break;
        payload->effect = func_080D4774(payload->effect);
        if (payload->effect != 0)
            break;
        payload->transition = func_080DBA5C(payload->transition);
        if (payload->transition == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
