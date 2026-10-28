/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F5208.c
 * Original SHA-256: ed7d1544056ad54033c17e342c00cb9c7e01117f6b0d4dbe00dd25583ebb49d1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
    u32 unknown_08[3];
    u16 unknown_14;
    u16 mode;
} Descriptor080F5208;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 unknown_06;
    u8 mode;
    u8 ready;
    u8 unknown_09[3];
    void *output;
    u32 coordinate_result;
    u32 input;
    void *initial_task;
    u8 unknown_1c[8];
    void *coordinate_task;
    void *effect_task;
    void *first_timeline_task;
    void *second_timeline_task;
    void *object_task;
    void *output_task;
    void *resource_task;
} Payload080F5208;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern u8 func_080D3B54(u32 input);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D4724(const void *resource, void *parent, u16 duration);
extern void *func_080D4774(void *task);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 count,
                         void *output, const void *resource, void *parent);
extern void *func_080D6134(void *task);
extern void func_080D7220(const void *resource, u8 second, u8 third,
                         s16 x, s16 y, u16 sixth);
extern u8 func_080D8858(u32 input, u16 flags);
extern u8 func_080D8B4C(void);
extern void *func_080DBA5C(void *task);
extern u8 func_080DBFFC(u32 input, u8 index);
extern void *func_080DCFE4(void *object, const void *resource, u8 mode,
                         u16 value, u16 count, void *parent, s16 extra);
extern void *func_080DD4A4(u32 input, u8 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 fourth);
extern void *func_080DDF68(u32 input, void **output, u16 flags, u8 mode,
                         u8 *ready, const void *resource, u16 seventh,
                         u16 eighth, void *parent);
extern u8 func_080DE1F0(void *output);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                         u16 fourth, void *parent);
extern void *func_080E03F8(u32 input, const void *resource, u8 mode,
                         u8 fourth, u32 fifth, void *parent);
extern void *func_080E05DC(void *task);

/* Target: complete [0x080F5208, 0x080F543C), 564 bytes: 518 code,
 * 44 literal and two internal zero alignment bytes. */
u32 func_080F5208(void *task, Descriptor080F5208 *descriptor,
                  Payload080F5208 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;
            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 4;
            if (payload->mode)
                mode = 0;
            payload->initial_task = func_080E03F8(payload->input,
                (const void *)0x0839B2AC, mode, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (func_080D3B54(payload->input)) {
            descriptor->phase = 2;
            break;
        }
        payload->output_task = func_080DDF68(payload->input, &payload->output,
            0x8007, 2, &payload->ready, (const void *)0x0839B320, 5, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (!payload->ready)
            break;
        func_080DBFFC(payload->input, 0);
        payload->countdown = 10;
        descriptor->phase++;
    case 0x102:
        {
            u8 busy;
            void *object;

            if (payload->countdown) {
                payload->countdown--;
                if (payload->countdown)
                    break;
            }
            busy = func_080D8B4C();
            if (busy)
                break;
            if (!func_080D8858(payload->input, 0)) {
                descriptor->phase = 2;
                break;
            }
            object = func_080DD4A4(payload->input, 0);
            payload->coordinate_result = func_080DD748(object,
                &payload->x, &payload->y, 0);
            func_080D7220((const void *)0x088F46F0, 0, 2,
                payload->x, (s16)(payload->y - 4), busy);
            payload->first_timeline_task = func_080D4704(
                (const void *)0x08949F68, task);
            payload->second_timeline_task = func_080D4724(
                (const void *)0x0894A9C8, task, 30);
            payload->effect_task = func_080D3E9C((const void *)0x0894D69C,
                task);
            payload->coordinate_task = func_080D6098(payload->x,
                (s16)(payload->y - 4), 0, 1, 2, payload->unknown_1c,
                (const void *)0x0839B2DC, task);
            payload->resource_task = func_080DFD8C((const void *)0x0839B328,
                1, 4, 0, task);
            payload->object_task = func_080DCFE4(object,
                (const void *)0x0839B30C, 12, 60, 4, task, 60);
            descriptor->phase++;
        }
        break;
    case 0x103:
        if (!func_080DE1F0(payload->output))
            break;
        payload->effect_task = func_080D3F08(payload->effect_task);
        if (payload->effect_task)
            break;
        payload->first_timeline_task = func_080D4774(payload->first_timeline_task);
        if (payload->first_timeline_task)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->second_timeline_task = func_080D4774(payload->second_timeline_task);
        if (payload->second_timeline_task)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
