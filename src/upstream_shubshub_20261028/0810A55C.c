/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810A55C.c
 * Original SHA-256: 42a1817b19826e7f8271f950e5f9b8e1de31f2d8d96bed40f1b09c4fb734a4d0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Target: complete [0x0810A55C, 0x0810A6E6), 394 bytes, 169 instructions.
 * Local offset views do not establish original types or storage extents.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 variant;
} Descriptor0810A55C;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u8 variant;
    u8 ready;
    u8 unknown_08[4];
    void *output;
    void *coordinate_result;
    void *actor;
    void *initial_task;
    u8 unknown_1c[16];
    void *effect_task;
    void *object_task;
    void *output_task;
    void *record_task;
} Payload0810A55C;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A1B9C[];
extern const u8 data_083A1C34[];
extern const u8 data_083A1BC0[];
extern const u8 data_083A1C20[];
extern const u8 data_083A1C38[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u8, u8, u8, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE244(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810A55C(void *task, Descriptor0810A55C *descriptor,
                  Payload0810A55C *payload)
{
    u8 animation;
    u8 blocked;
    u16 output_mode;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 3;
        if (payload->variant != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_task = func_080E03F8(payload->actor, data_083A1B9C,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        blocked = func_080D3B54(payload->actor);
        if (blocked != 0) {
            descriptor->phase = 2;
            break;
        }
        output_mode = 92;
        if (payload->mode != 0)
            output_mode = 40;
        payload->output_task = func_080DDF68(payload->actor, &payload->output,
            output_mode, 1, &payload->ready, data_083A1C34,
            blocked, blocked, task);
        descriptor->phase++;
        break;
    case 0x101: {
        void *actor_object;
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1,
            4, payload->unknown_1c, data_083A1BC0, task);
        payload->object_task = func_080DCFE4(actor_object, data_083A1C20,
            12, 50, 4, task, 60);
        payload->record_task = func_080DFD8C(data_083A1C38, 2, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x102:
        if (func_080DE244(payload->output) == 0)
            break;
        payload->effect_task = func_080D6134(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
