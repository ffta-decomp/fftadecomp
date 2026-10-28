/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F4450.c
 * Original SHA-256: b14d982935eda5ed1088e2f3da84406edadaf00768075aeeaaaad7ea0311db9a
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
} Descriptor080F4450;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u16 countdown;
    void *object;
    u32 coordinate_result;
    void *timeline_task;
    u32 unknown_14;
    void *coordinate_task;
    u32 input;
    void *initial_task;
    void *object_task;
    void *final_task;
} Payload080F4450;

extern void func_080D38B4(void);
extern u32 func_080D3B54(u32 input);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D4774(void *task);
extern void *func_080D6098(s16 x, s16 y, u16 value, u8 mode,
                         u16 count, void *output, const void *resource,
                         void *parent);
extern void *func_080D6134(void *task);
extern u32 func_080D8858(u32 input, u16 index);
extern u32 func_080D8B4C(void);
extern void *func_080DBA5C(void *task);
extern void *func_080DBB14(void *object, u8 mode, u8 value, u16 fourth,
                         void *parent);
extern void func_080DC058(u32 input, u8 index);
extern void *func_080DD47C(u32 input);
extern void *func_080DD4A4(u32 input, u8 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void func_080DE10C(void *object, u16 value);
extern void func_080DE3BC(void *object, u8 mode);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                         u16 value, void *parent);
extern void *func_080E03F8(u32 input, const void *resource, u8 mode,
                         u8 fourth, u32 fifth, void *parent);
extern void *func_080E05DC(void *task);

/* Target: complete [0x080F4450, 0x080F4612), 450 bytes: 414 code,
 * 28 literal and eight internal zero alignment bytes. */
u32 func_080F4450(void *task, Descriptor080F4450 *descriptor,
                  Payload080F4450 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;

            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 2;
            if (payload->mode)
                mode = 0;
            payload->initial_task = func_080E03F8(payload->input,
                (const void *)0x0839B04C, mode, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if ((u8)func_080D3B54(payload->input)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD47C(payload->input);
        func_080DE10C(payload->object, 0x24);
        func_080DE3BC(payload->object, 1);
        payload->countdown = 30;
        descriptor->phase++;
        break;
    case 0x101:
        payload->countdown--;
        if (payload->countdown)
            break;
        payload->object_task = func_080DBB14(payload->object, 1, 12, 0, task);
        payload->timeline_task = func_080D4704((const void *)0x0894848C,
                                             task);
        payload->final_task = func_080DFD8C((const void *)0x0839B07C,
                                          1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task)
            break;
        func_080DC058(payload->input, 0);
        payload->countdown = 10;
        descriptor->phase++;
    case 0x103:
        if (payload->countdown) {
            payload->countdown--;
            if (payload->countdown)
                break;
        }
        if ((u8)func_080D8B4C())
            break;
        if (!(u8)func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->coordinate_result = func_080DD748(
            func_080DD4A4(payload->input, 0), &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 1, &payload->unknown_14, (const void *)0x0839B064, task);
        payload->final_task = func_080DFD8C((const void *)0x0839B084,
                                          1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
