/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08109990.c
 * Original SHA-256: 03a315c548107bce6897704afbbcc5465769d6d3d9464c154d8a077c8116b060
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Target: complete [0x08109990, 0x08109B62), 466 bytes, 200 instructions.
 * These local offset views do not establish original types or storage extents.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 flag;
} Descriptor08109990;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u8 flag;
    s8 saved_byte;
    u8 ready;
    u8 unknown_09[3];
    void *output;
    void *coordinate_result;
    void *actor;
    void *initial_task;
    u8 unknown_1c[12];
    void *effect_task;
    void *object_task;
    void *output_task;
    void *record_task;
} Payload08109990;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A1858[];
extern const u8 data_083A18CC[];
extern const u8 data_083A1870[];
extern const u8 data_083A18B8[];
extern const u8 data_083A18D0[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern s8 func_080DBC88(void *);
extern void *func_080DD47C(void *);
extern int func_080DBCD4(void *, void *);
extern void func_080DBC90(void *, s8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080D6098(s16, s16, u8, u8, u8, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE244(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08109990(void *task, Descriptor08109990 *descriptor,
                  Payload08109990 *payload)
{
    u8 animation;
    u8 blocked;
    u16 output_mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 2;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_task = func_080E03F8(payload->actor, data_083A1858,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        void *actor_object;
        void *state_object;
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        blocked = func_080D3B54(payload->actor);
        if (blocked != 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        state_object = func_080DD4C4(actor_object);
        payload->saved_byte = func_080DBC88(state_object);
        payload->output = func_080DD47C(payload->actor);
        func_080DBC90(state_object,
            (s8)func_080DBCD4(payload->output, state_object));
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        output_mode = 92;
        if (payload->mode != 0)
            output_mode = 52;
        payload->output_task = func_080DDF68(payload->actor, &payload->output,
            output_mode, 1, &payload->ready, data_083A18CC,
            blocked, blocked, task);
        descriptor->phase++;
        break;
    }
    case 0x101: {
        void *actor_object;
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1,
            3, payload->unknown_1c, data_083A1870, task);
        payload->object_task = func_080DCFE4(actor_object, data_083A18B8,
            12, 35, 12, task, 35);
        payload->record_task = func_080DFD8C(data_083A18D0, 3, 4, 0, task);
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
        func_080DBC90(payload->coordinate_result, payload->saved_byte);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
