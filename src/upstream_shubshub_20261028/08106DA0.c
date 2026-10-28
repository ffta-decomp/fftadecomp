/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08106DA0.c
 * Original SHA-256: 9a423a58fd00404ae751736f362e8948c7ec19e51a874b16202dd48f8be3e8da
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* Target: complete [0x08106DA0, 0x08106F38), 408 bytes, 167 instructions.
 * These local offset views do not establish original storage extents or types.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor08106DA0;

typedef struct {
    u16 countdown;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *coordinate_result;
    u8 unknown_0c[8];
    void *coordinate_task;
    void *resource_task;
    void *timeline;
    void *initial_task;
    void *actor;
    void *object_task;
    void *output_task;
} Payload08106DA0;

extern const u8 data_083A08CC[];
extern const u8 data_083A0908[];
extern const u8 data_083A0938[];
extern const u8 data_083A094C[];
extern const u8 data_088F46AC[];
extern const u8 data_08948CC4[];
extern const u8 data_0894D69C[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08106DA0(void *task, Descriptor08106DA0 *descriptor,
                  Payload08106DA0 *payload)
{
    void *actor;
    void *object;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 5;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_083A08CC,
            mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_0c, data_083A0908, task);
        payload->object_task = func_080DCFE4(object, data_083A0938,
            12, 80, 4, task, 80);
        payload->output_task = func_080DFD8C(data_083A094C, 3, 4, 0, task);
        payload->countdown = 20;
        descriptor->phase++;
        break;
    case 0x101:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080D7220(data_088F46AC, 0, 2, payload->x, payload->y, 0);
        payload->resource_task = func_080D4724(data_08948CC4, task, 2);
        payload->timeline = func_080D3E9C(data_0894D69C, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->resource_task = func_080D4774(payload->resource_task);
        if (payload->resource_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
