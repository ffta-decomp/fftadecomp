/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F33A4.c
 * Original SHA-256: 9b07f8aa951796a5a9fe5c3123138d643aaa9c0a76d3477ebdc228b80367f3ed
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
    u8 unknown_08[0x0E];
    u16 mode;
} Descriptor080F33A4;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04;
    u8 mode;
    u8 ready;
    u8 unknown_07;
    void *output;
    u32 coordinate_result;
    u32 input;
    void *initial_task;
    u8 unknown_18[8];
    void *coordinate_task;
    void *effect_task;
    void *ready_task;
    void *resource_task;
} Payload080F33A4;

extern void *func_080E03F8(u32 input, const void *resource, u8 mode,
                          u8 fourth, u32 fifth, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *task);
extern u8 func_080D3B54(u32 input);
extern void *func_080DDF68(u32 input, void **output, u16 flags, u8 mode,
                          u8 *ready, const void *resource, u16 seventh,
                          u16 eighth, void *parent);
extern u8 func_080DBFFC(u32 input, u8 index);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(u32 input, u16 flags);
extern void *func_080DD4A4(u32 input, u8 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 fourth);
extern u8 func_080DD580(void *object);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 fifth,
                          void *output, const void *resource, void *parent);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 third,
                          u16 fourth, void *parent);
extern void *func_080DCFE4(void *object, const void *resource, u8 third,
                          u16 fourth, u16 fifth, void *parent, s16 seventh);
extern u8 func_080DE1F0(void *object);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

/* Target: complete [0x080F33A4, 0x080F353A), 406 bytes, including
 * 376 code bytes, 24 literal bytes and six internal alignment bytes.
 * The address at +18 is passed without an inferred pointee type or extent. */
u32 func_080F33A4(void *task, Descriptor080F33A4 *descriptor,
                  Payload080F33A4 *payload)
{
    void *object;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->input = descriptor->input;
        mode = 3;
        if (payload->mode)
            mode = 0;
        payload->initial_task = func_080E03F8(payload->input,
            (const void *)0x0839AAFC, mode, 0, 0, task);
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
        payload->ready_task = func_080DDF68(payload->input,
            &payload->output, 0x8007, 2, &payload->ready,
            (const void *)0x0839AB64, 0x23, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (!payload->ready)
            break;
        func_080DBFFC(payload->input, 0);
        descriptor->phase++;
    case 0x102:
        if (func_080D8B4C())
            break;
        if (!func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->input, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        if (func_080DD580(object)) {
            payload->coordinate_task = func_080D6098(payload->x, payload->y,
                0, 1, 2, payload->unknown_18, (const void *)0x0839AB20, task);
            payload->resource_task = func_080DFD8C((const void *)0x0839AB6C,
                2, 4, 0, task);
        }
        payload->effect_task = func_080DCFE4(object, (const void *)0x0839AB50,
            12, 15, 4, task, 10);
        descriptor->phase++;
        break;
    case 0x103:
        if (!func_080DE1F0(payload->output))
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
