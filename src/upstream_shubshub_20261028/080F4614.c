/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F4614.c
 * Original SHA-256: 1fa986f4edd4e17978670a2cd04093a2dd7c8d98dfd7b2c899544e5433ae2b92
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
    s16 id;
    u16 mode;
} Descriptor080F4614;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 variant;
    u8 mode;
    u8 ready;
    u8 unknown_09[3];
    void *output;
    u32 coordinate_result;
    void *object;
    u32 input;
    void *initial_task;
    u8 unknown_20[8];
    void *coordinate_task;
    u8 unknown_2c[4];
    void *second_coordinate_task;
    void *unknown_34;
    void *effect_task;
    void *output_task;
    void *resource_task;
} Payload080F4614;

extern void *func_080E03F8(u32 input, const void *resource, u8 mode,
                         u8 fourth, u32 fifth, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *task);
extern void func_080D45D0(const void *resource, u8 second, u8 third,
                         u8 fourth, u8 fifth);
extern u8 func_080D3B54(u32 input);
extern void *func_080DDF68(u32 input, void **output, u16 flags, u8 mode,
                         u8 *ready, const void *resource, u16 seventh,
                         u16 eighth, void *parent);
extern u8 func_080DBFFC(u32 input, u8 index);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(u32 input, u16 flags);
extern void *func_080DD4A4(u32 input, u8 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 fourth);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 fifth,
                         void *output, const void *resource, void *parent);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 third,
                         u16 fourth, void *parent);
extern void *func_080DCFE4(void *object, const void *resource, u8 third,
                         u16 fourth, u16 fifth, void *parent, s16 seventh);
extern u8 func_080A8858(void *object, u8 index);
extern void *func_080D6134(void *task);
extern u8 func_080DE1F0(void *object);
extern void *func_080DBA5C(void *task);

/* Target: complete [0x080F4614, 0x080F488A), 630 bytes: 578 code,
 * 48 literal and four internal alignment bytes. The resource selection uses
 * an observed 20-byte stride, without assigning a resource object extent. */
u32 func_080F4614(void *task, Descriptor080F4614 *descriptor,
                  Payload080F4614 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;
            payload->variant = 0;
            if (descriptor->id == 0x5c)
                payload->variant = 1;
            else if (descriptor->id == 0xb5)
                payload->variant = 2;
            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 4;
            if (payload->mode)
                mode = 0;
            payload->initial_task = func_080E03F8(payload->input,
                (const void *)0x0839B0C4, mode, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (payload->variant == 1) {
            func_080D45D0((const void *)0x088EA7F0, 6, 1, 0, 1);
            func_080D45D0((const void *)0x088E9C70, 7, 1, 0, 1);
        }
        if (func_080D3B54(payload->input)) {
            descriptor->phase = 2;
            break;
        }
        payload->output_task = func_080DDF68(payload->input,
            &payload->output, 0x8007, 2, &payload->ready,
            (const void *)0x0839B178, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (!payload->ready)
            break;
        func_080DBFFC(payload->input, 0);
        payload->countdown = 6;
        descriptor->phase++;
    case 0x102:
        if (payload->countdown) {
            payload->countdown--;
            if (payload->countdown)
                break;
        }
        if (func_080D8B4C())
            break;
        if (!func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD4A4(payload->input, 0);
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_20, (const void *)0x0839B0F4, task);
        payload->resource_task = func_080DFD8C((const void *)0x0839B180,
            1, 4, 0, task);
        payload->effect_task = func_080DCFE4(payload->object,
            (const u8 *)0x0839B13C + 20 * payload->variant,
            12, 0, 4, task, 0);
        if (func_080A8858(payload->object, 3)) {
            if (payload->variant == 2) {
                payload->second_coordinate_task = func_080D6098(
                    payload->x, payload->y, 0, 1, 1, payload->unknown_2c,
                    (const void *)0x0839B124, task);
                payload->resource_task = func_080DFD8C((const void *)0x0839B188,
                    1, 4, 0, task);
            }
            descriptor->phase++;
        } else {
            descriptor->phase = 0x104;
        }
        break;
    case 0x103:
        payload->second_coordinate_task = func_080D6134(
            payload->second_coordinate_task);
        if (payload->second_coordinate_task)
            break;
        descriptor->phase++;
        break;
    case 0x104:
        if (!func_080DE1F0(payload->output))
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task)
            break;
        payload->unknown_34 = func_080DBA5C(payload->unknown_34);
        if (payload->unknown_34)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
