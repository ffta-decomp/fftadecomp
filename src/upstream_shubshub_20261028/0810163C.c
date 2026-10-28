/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810163C.c
 * Original SHA-256: 8818d3caba7f69ea8e7de383e1e0c11b90203eaa3f56a082e47a92cdac337069
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08[3];
    u16 id;
    u16 variant;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 countdown;
    u8 variant;
    u8 status;
    s16 x;
    s16 y;
    void *child;
    u32 unknown_0c;
    void *coordinate_result;
    void *actor_object;
    void *coordinate_task;
    u8 unknown_1c[16];
    void *sprite;
    void *resource_task;
    void *effect_task;
    void *actor;
    void *stage;
    u32 unknown_40;
    void *actor_task;
    u32 unknown_48;
    void *retained_task;
    struct InterpolationState y_motion;
};

extern const u8 data_0839EB94[];
extern const u8 data_0839EBC4[];
extern const u8 data_0894AD30[];
extern const u8 data_0839EC24[];
extern const u8 data_0839EC38[];
extern const u8 data_088F0800[];
extern const u8 data_0894DAB0[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_08102B48(void *, u8, u8 *, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BDA4(void *, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern void func_0800BC08(u32, s16, s16);
extern u8 func_080E0690(struct InterpolationState *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern void func_080D4D14(void *, u8);
extern void *func_080D6134(void *);
extern void *func_08102BA8(void *);
extern void *func_080DBA5C(void *);

/* Target: complete [0x0810163C, 0x0810188C), 592 bytes:
 * 540 code bytes, 44 literal bytes and eight internal alignment bytes. */
u32 func_0810163C(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->variant)
            mode = 0;
        payload->stage = func_080E03F8(payload->actor, data_0839EB94,
                                      mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        payload->child = func_08102B48(payload->actor, 0, &payload->status, task);
        if (!payload->child)
            descriptor->phase = 2;
        else
            descriptor->phase++;
        break;
    case 0x101:
        if (!payload->status)
            break;
        if (payload->status == 2) {
            descriptor->phase = 0x104;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
                                                 &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y, 0, 1,
                                       4, payload->unknown_1c, data_0839EBC4, task);
        payload->effect_task = func_080D4704(data_0894AD30, task);
        payload->actor_task = func_080DCFE4(payload->actor_object,
                                      data_0839EC24, 12, 64, 4, task, 64);
        payload->retained_task = func_080DFD8C(data_0839EC38, 2, 4, 0, task);
        payload->countdown = 8;
        descriptor->phase++;
        break;
    case 0x102:
        if (--payload->countdown != 0)
            break;
        func_080D49FC(0, 2, 0, payload->x, (s16)(payload->y - 32));
        payload->sprite = func_080D4B64(0, data_088F0800, 996, 6);
        func_0800BDA4(payload->sprite, 1);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->resource_task = func_080D3E9C(data_0894DAB0, task);
        func_080E0608(&payload->y_motion, (s16)(payload->y - 32), payload->y, 64);
        descriptor->phase++;
        break;
    case 0x103:
        func_080E064C(&payload->y_motion);
        func_0800BC08(0, payload->x, payload->y_motion.current);
        if (func_080E0690(&payload->y_motion))
            descriptor->phase++;
        break;
    case 0x104:
        payload->effect_task = func_080D4774(payload->effect_task);
        if (payload->effect_task)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        if (payload->sprite) {
            u32 mask;
            func_080D4D14(payload->sprite, 0);
            payload->sprite = 0;
            mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->child = func_08102BA8(payload->child);
        if (payload->child)
            break;
        payload->actor_task = func_080DBA5C(payload->actor_task);
        if (!payload->actor_task)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
