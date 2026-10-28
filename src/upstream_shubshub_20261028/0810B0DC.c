/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810B0DC.c
 * Original SHA-256: aa0c4e600d50a3de227868d2a044c531c895eff3cea1e23a62adc02a1d8f9128
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Target: complete [0x0810B0DC, 0x0810B25A), 382 bytes, 161 instructions.
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
} Descriptor0810B0DC;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u8 flag;
    u8 setup_signal;
    u8 ready;
    u8 unknown_09[3];
    void *output;
    void *coordinate_result;
    void *actor_object;
    void *actor;
    void *initial_task;
    u8 unknown_20[4];
    void *effect_task;
    void *object_task;
    void *output_task;
    void *record_task;
} Payload0810B0DC;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A1E48[];
extern const u8 data_083A1E8C[];
extern const u8 data_083A1E60[];
extern const u8 data_083A1E78[];
extern const u8 data_083A1E94[];

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

u32 func_0810B0DC(void *task, Descriptor0810B0DC *descriptor,
                  Payload0810B0DC *payload)
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
        payload->initial_task = func_080E03F8(payload->actor, data_083A1E48,
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
        output_mode = 84;
        if (payload->mode != 0)
            output_mode = 52;
        payload->output_task = func_080DDF68(payload->actor, &payload->output,
            output_mode, 2, &payload->setup_signal, data_083A1E8C,
            blocked, blocked, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        payload->effect_task = func_080D6098(payload->x, payload->y, 0, 1,
            1, payload->unknown_20, data_083A1E60, task);
        payload->object_task = func_080DCFE4(payload->actor_object, data_083A1E78,
            12, 20, 4, task, 20);
        payload->record_task = func_080DFD8C(data_083A1E94, 1, 4, 0, task);
        descriptor->phase++;
        break;
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
