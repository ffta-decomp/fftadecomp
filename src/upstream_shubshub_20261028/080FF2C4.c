/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FF2C4.c
 * Original SHA-256: 14cb17da50611470e19ee7d6a65781383e388501c789b395c37a7b1abcdc520b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08[3];
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
    u8 variant;
    u8 index;
    u16 counter;
    u8 selector;
    u8 unknown_05;
    s16 x;
    s16 y;
    u16 unknown_0a;
    void *lanes[3];
    void *coordinate_task;
    void *resource_task;
    void *effect_task;
    struct InterpolationState x_motion;
    struct InterpolationState y_motion;
    void *retained_task;
};

struct CoordinateOffset {
    u16 x;
    u16 y;
};

extern const u8 data_088F5A48[];
extern const u8 data_0894D95C[];
extern const u8 data_0839E2F8[];
extern const u8 data_0894AD30[];
extern const u8 data_0839E38C[];
extern const u8 data_0839E358[];
extern const u8 data_0839E388[];
extern const u16 data_0839E39C[];
extern const u16 data_0839E3A2[];
extern u16 g_control_flags_03000940;

extern void *func_080DD748(void *, s16 *, s16 *, int);
extern s8 func_080DBC88(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern void func_080D615C(void *, s16, s16, s16);
extern u8 func_080E0690(struct InterpolationState *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(u8);
extern void *func_080D4774(void *);

/* Target: complete [0x080FF2C4, 0x080FF5C8), 772 bytes:
 * 706 code bytes, 60 literal bytes and six internal alignment bytes. */
u32 func_080FF2C4(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    u8 lane;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->selector = func_080DBC88(func_080DD748(descriptor->actor,
                                       &payload->x, &payload->y, 0));
        break;
    case 0x100:
        payload->y -= 24;
        func_080D7220(data_088F5A48, 0, 2, payload->x, payload->y, 0);
        payload->resource_task = func_080D3E9C(data_0894D95C, task);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
                              0, 0, 3, payload->lanes, data_0839E2F8, task);
        payload->effect_task = func_080D4724(data_0894AD30, task, 165);
        payload->retained_task = func_080DFD8C(data_0839E38C, 2, 4, 0, task);
        payload->counter = 12;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->counter != 0) {
            const struct CoordinateOffset *offset;
            if (--payload->counter != 0)
                break;
            offset = (const struct CoordinateOffset *)(data_0839E358
                    + 24 * payload->variant + 12 * (payload->selector >> 1)
                    + 4 * payload->index);
            func_080E0608(&payload->x_motion, payload->x,
                         (s16)(payload->x + offset->x), data_0839E388[payload->index]);
            func_080E0608(&payload->y_motion, payload->y,
                         (s16)(payload->y + offset->y), data_0839E388[payload->index]);
            payload->index++;
        }
        for (lane = 0; lane < 3; lane++) {
            if (payload->lanes[lane] != 0) {
                s16 x = payload->x + data_0839E39C[lane];
                s16 y = payload->y + data_0839E3A2[lane];
                func_080107D4(payload->lanes[lane], x, y, 0);
            }
        }
        func_080D7220(data_088F5A48, 0, 2, payload->x, payload->y, 0);
        func_080E064C(&payload->x_motion);
        func_080E064C(&payload->y_motion);
        payload->x = payload->x_motion.current;
        payload->y = payload->y_motion.current;
        func_080D615C(payload->coordinate_task, payload->x, payload->y, 0);
        if (!func_080E0690(&payload->x_motion))
            break;
        if (payload->index <= 2) {
            const struct CoordinateOffset *offset;
            offset = (const struct CoordinateOffset *)(data_0839E358
                    + 24 * payload->variant + 12 * (payload->selector >> 1)
                    + 4 * payload->index);
            func_080E0608(&payload->x_motion, payload->x,
                         (s16)(payload->x + offset->x), data_0839E388[payload->index]);
            func_080E0608(&payload->y_motion, payload->y,
                         (s16)(payload->y + offset->y), data_0839E388[payload->index]);
            payload->index++;
        } else {
            descriptor->phase++;
        }
        break;
    case 0x102:
        for (lane = 0; lane < 3; lane++) {
            if (payload->lanes[lane] != 0) {
                s16 x = payload->x + data_0839E39C[lane];
                s16 y = payload->y + data_0839E3A2[lane];
                func_080107D4(payload->lanes[lane], x, y, 0);
            }
        }
        func_080D7220(data_088F5A48, 0, 2, payload->x, payload->y, 0);
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->effect_task = func_080D4774(payload->effect_task);
        if (payload->effect_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
