/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0810E44C.c
 * Original SHA-256: 6a2f756894358dfc164bb4ae102106368280b08e0d31fba59fa117d12d7a34b8
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
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
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
    s16 x;
    s16 y;
    u8 mode;
    u8 variant;
    u16 unknown_06;
    void *object;
    void *coordinate_task;
    void *sprite;
    void *resource_task;
    void *coordinate_result;
    void *actor_object;
    void *first_task;
    void *second_task;
    void *actor;
    void *initial_task;
    void *actor_task;
    struct InterpolationState y_motion;
    void *retained_task;
};

/* Address bindings only; original resource declarations and extents are unknown. */
extern const u8 data_083A2BA8[];
extern const u8 data_088F66B4[];
extern const u8 data_0894DE44[];
extern const u8 data_0850875C[];
extern const u8 data_083A2C1C[];
extern const u8 data_088EF6CC[];
extern const u8 data_0894D69C[];
extern const u8 data_0894A0E8[];
extern const u8 data_0894AAB0[];
extern const u8 data_083A2BF0[];
extern const u8 data_083A2C24[];
extern const u8 data_083A2C08[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern void func_080D7468(const void *, u8, s16, s16);
extern void func_080107D4(void *, s16, s16, u8);
extern void *func_080D3F08(void *);
extern u8 func_080E0690(struct InterpolationState *);
extern u32 func_080035A8(u8);
extern void func_08011428(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4D2C(void *, u8);
extern u8 func_080D48DC(void **, u8);
extern void *func_080D6134(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DBA5C(void *);

/* Target: complete [0x0810E44C, 0x0810E736), 746 bytes, 300 instructions. */
u32 func_0810E44C(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 animation;
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        if (descriptor->flags & 2)
            payload->mode = 1;
        animation = 6;
        if (payload->variant)
            animation = 0;
        payload->initial_task = func_080E03F8(payload->actor, data_083A2BA8,
                                             animation, 1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
                                                  &payload->x, &payload->y, 0);
        func_080D7220(data_088F66B4, 1, 3, payload->x,
                      (s16)(payload->y - 128), 0);
        payload->resource_task = func_080D3E9C(data_0894DE44, task);
        payload->object = func_080D5CC0(data_0850875C, 0, payload->x,
                            (s16)(payload->y - 128), 1014, 7, 1, 0);
        payload->retained_task = func_080DFD8C(data_083A2C1C, 1, 4, 0, task);
        func_080E0608(&payload->y_motion, (s16)(payload->y - 128),
                      (s16)(payload->y - 8), 60);
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->y_motion);
        func_080D7468(data_088F66B4, 3, payload->x, payload->y_motion.current);
        func_080107D4(payload->object, payload->x, payload->y_motion.current, 0);
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        if (!func_080E0690(&payload->y_motion))
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        func_08011428(payload->object);
        payload->object = 0;
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->sprite = func_080D4B64(0, data_088EF6CC, 876, 7);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->resource_task = func_080D3E9C(data_0894D69C, task);
        payload->first_task = func_080D4704(data_0894A0E8, task);
        payload->second_task = func_080D4724(data_0894AAB0, task, 26);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
                                   0, 1, 1, &payload->object, data_083A2BF0, task);
        payload->retained_task = func_080DFD8C(data_083A2C24, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        if (func_080D48DC(&payload->first_task, 2))
            descriptor->phase++;
        break;
    case 0x103:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->actor_task = func_080DCFE4(payload->actor_object, data_083A2C08,
                                          12, 0, 12, task, 0);
        descriptor->phase++;
        break;
    case 0x104:
        payload->actor_task = func_080DBA5C(payload->actor_task);
        if (!payload->actor_task)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
