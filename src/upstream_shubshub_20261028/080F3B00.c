/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F3B00.c
 * Original SHA-256: 716f438bd885f8ab404ef551f53e6a4f470b84aad38365a0e3303c0596c9c96a
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
} Descriptor080F3B00;

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
    u32 unknown_18[3];
    void *coordinate_task;
    void *timeline_task;
    void *first_task;
    void *second_task;
    void *output_task;
    void *final_task;
} Payload080F3B00;

extern void func_080D38B4(void);
extern u32 func_080D3B54(u32 input);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D4774(void *task);
extern void *func_080D6098(s16 x, s16 y, u16 value, u8 mode,
                         u16 count, void *output, const void *resource,
                         void *parent);
extern void *func_080D6134(void *task);
extern u32 func_080D8858(u32 input, u16 index);
extern void *func_080DBA5C(void *task);
extern void *func_080DCFE4(void *object, const void *resource, u8 mode,
                         u16 value, u16 count, void *parent, s16 extra);
extern void *func_080DD4A4(u32 input, u8 index);
extern u32 func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void *func_080DDF68(u32 input, void **output, u16 value, u8 mode,
                         void *flag, const void *resource, u32 seventh,
                         u32 eighth, void *parent);
extern u32 func_080DE1F0(void *output);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                         u16 value, void *parent);
extern void *func_080E03F8(u32 input, const void *resource, u8 mode,
                         u8 fourth, u32 fifth, void *parent);
extern void *func_080E05DC(void *task);

/* Target: complete [0x080F3B00, 0x080F3CCC), 460 bytes: 428 code, 28 literal and four internal zero alignment bytes. */
u32 func_080F3B00(void *task, Descriptor080F3B00 *descriptor,
                  Payload080F3B00 *payload)
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
                (const void *)0x0839AD48, mode, 0, 0, task);
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
        payload->output_task = func_080DDF68(payload->input, &payload->output,
            0x28, 2, &payload->ready, (const void *)0x0839ADD4, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        {
            u8 status;
            void *object;
            const void *resource;

            if (!payload->ready)
                break;
            status = func_080D8858(payload->input, 0);
            if (!status) {
                descriptor->phase = 2;
                break;
            }
            object = func_080DD4A4(payload->input, 0);
            payload->coordinate_result = func_080DD748(object,
                &payload->x, &payload->y, 0);
            payload->coordinate_task = func_080D6098(payload->x, payload->y,
                0, 1, 3, payload->unknown_18, (const void *)0x0839AD78, task);
            payload->timeline_task = func_080D4704((const void *)0x0894AD30,
                                                 task);
            /* plausible: observed ROM address loaded from literal 0x080F3C74 for both DCFE4 calls. */
            resource = (const void *)0x0839ADC0;
            payload->first_task = func_080DCFE4(object, resource,
                                                12, 20, 4, task, 20);
            if (status == 2) {
                object = func_080DD4A4(payload->input, 1);
                payload->second_task = func_080DCFE4(object, resource,
                                                     12, 70, 10, task, -1);
            }
            payload->final_task = func_080DFD8C((const void *)0x0839ADDC,
                                                2, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!(u8)func_080DE1F0(payload->output))
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->first_task = func_080DBA5C(payload->first_task);
        if (payload->first_task)
            break;
        payload->second_task = func_080DBA5C(payload->second_task);
        if (payload->second_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
