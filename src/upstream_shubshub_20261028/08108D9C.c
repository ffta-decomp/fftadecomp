/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08108D9C.c
 * Original SHA-256: 6714e8a4494bd3af2435df10d8b2624d35476148efab326e308aa1a2fb3af15e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Target: complete [0x08108D9C, 0x08108F84), 488 bytes, 201 instructions.
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
} Descriptor08108D9C;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_07[2];
    u8 mode;
    u8 unknown_0a;
    u8 flag;
    void *output;
    void *coordinate_result;
    void *actor_object;
    void *resource_task;
    void *timeline;
    void *initial_task;
    void *actor;
    void *output_task;
    void *object_task;
    void *record_task;
} Payload08108D9C;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A11E0[];
extern const u8 data_083A120C[];
extern const void *const data_083A1204[];
extern const u8 data_088ED3F0[];
extern const u8 data_0894D6B4[];
extern const u8 data_083A1210[];
extern const u8 data_083A1224[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080DBA5C(void *);

u32 func_08108D9C(void *task, Descriptor08108D9C *descriptor,
                  Payload08108D9C *payload)
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
        payload->initial_task = func_080E03F8(payload->actor, data_083A11E0,
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
        payload->output = func_080DD47C(payload->actor);
        payload->output_task = func_080DDF68(payload->actor, &payload->output,
            output_mode, data_083A120C[payload->mode], &payload->ready,
            data_083A1204[payload->mode], blocked, blocked, task);
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
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->resource_task = func_080D4B64(0, data_088ED3F0, 943, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->timeline = func_080D3E9C(data_0894D6B4, task);
        payload->object_task = func_080DCFE4(payload->actor_object,
            data_083A1210, 12, 52, 12, task, 52);
        payload->record_task = func_080DFD8C(data_083A1224, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->resource_task = func_080D4D2C(payload->resource_task, 0);
        if (payload->resource_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
