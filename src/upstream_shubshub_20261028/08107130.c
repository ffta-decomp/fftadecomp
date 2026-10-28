/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08107130.c
 * Original SHA-256: da87de086ea2c41c1fa603dcbc96be2f8dcc5693bdc15d95cedc84100797e294
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* Target: complete [0x08107130, 0x081072AE), 382 bytes, 161 instructions.
 * These local offset views do not establish original storage extents or types.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 flag;
} Descriptor08107130;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u8 flag;
    u8 ready;
    u32 unknown_08;
    void *output;
    void *coordinate_result;
    void *actor;
    void *initial_child;
    u8 unknown_1c[0x20];
    void *coordinate_child;
    void *effect_child;
    void *output_child;
    void *record_child;
} Payload08107130;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A0A38[];
extern const u8 data_083A0B30[];
extern const u8 data_083A0A5C[];
extern const u8 data_083A0B1C[];
extern const u8 data_083A0B34[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE244(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08107130(void *task, Descriptor08107130 *descriptor,
                  Payload08107130 *payload)
{
    void *actor_object;
    u8 animation;
    u16 output_mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 3;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_child = func_080E03F8(payload->actor, data_083A0A38,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor) != 0) {
            descriptor->phase = 2;
            break;
        }
        output_mode = 84;
        if (payload->mode != 0)
            output_mode = 52;
        payload->output_child = func_080DDF68(payload->actor, &payload->output,
            output_mode, 1, &payload->ready, data_083A0B30, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 8, payload->unknown_1c, data_083A0A5C, task);
        payload->effect_child = func_080DCFE4(actor_object, data_083A0B1C,
            12, 50, 4, task, 60);
        payload->record_child = func_080DFD8C(data_083A0B34, 8, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (func_080DE244(payload->output) == 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
