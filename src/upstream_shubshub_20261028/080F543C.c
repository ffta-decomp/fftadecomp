/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F543C.c
 * Original SHA-256: d6e225513a0d29d1e2636ca9dacc7275b337caac9b1f98aab0cb38c4028ccdf5
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
} Descriptor080F543C;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 mode;
    u8 unknown_07;
    void *object;
    u32 unknown_0c;
    u32 unknown_10;
    void *coordinate_task;
    void *resource_task;
    void *timeline_task;
    void *later_timeline_task;
    void *object_task;
    void *retained_task;
    void *initial_task;
    u32 input;
} Payload080F543C;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D3F08(void *task);
extern void func_080D3F84(void *task, u8 first, u8 second);
extern void func_080D45D0(const void *resource, u8 first, u8 second,
                         u8 third, u8 count);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D4774(void *task);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 count,
                         void *output, const void *resource, void *parent);
extern void *func_080D6134(void *task);
extern void func_080D7220(const void *resource, u8 first, u8 second,
                         s16 x, s16 y, u16 flags);
extern u32 func_080D8858(u32 input, u16 index);
extern void *func_080DBA5C(void *task);
extern void *func_080DBB14(void *object, u8 mode, u8 value, u16 fourth,
                         void *parent);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080DD47C(u32 input);
extern void func_080DE10C(void *object, u16 value);
extern void func_080DE3BC(void *object, u8 mode);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                         u16 fourth, void *parent);
extern void *func_080E03F8(u32 input, const void *resource, u8 mode,
                         u8 fourth, u32 fifth, void *parent);
extern void *func_080E05DC(void *task);

/* Target: complete [0x080F543C, 0x080F5710), 724 bytes: 648 code,
 * 68 literal and eight internal zero alignment bytes. */
u32 func_080F543C(void *task, Descriptor080F543C *descriptor,
                  Payload080F543C *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;

            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 6;
            if (payload->mode)
                mode = 0;
            payload->initial_task = func_080E03F8(payload->input,
                (const void *)0x0839B368, mode, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (!(u8)func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD47C(payload->input);
        func_080DE10C(payload->object, 0x24);
        func_080DE3BC(payload->object, 1);
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        payload->coordinate_task = func_080D6098(payload->x,
            (s16)(payload->y + 16), 0, 1, 1, &payload->unknown_10,
            (const void *)0x0839B3B0, task);
        payload->retained_task = func_080DFD8C((const void *)0x0839B3C8,
                                             3, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        {
            void *coordinate_task;

            coordinate_task = func_080D6134(payload->coordinate_task);
            payload->coordinate_task = coordinate_task;
            if (coordinate_task)
                break;
            func_080D45D0((const void *)0x088E9DBC, 6, 0, 0, 1);
            func_080D7220((const void *)0x088F46D8, 0, 2,
                payload->x, payload->y, (u32)coordinate_task);
            payload->timeline_task = func_080D4704((const void *)0x08948D38,
                                                  task);
            payload->resource_task = func_080D3E9C((const void *)0x0894D6D4,
                                                  task);
            {
                u32 mask = func_080035A8(2);
                u16 flags = g_control_flags_03000940;
                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->object_task = func_080DBB14(payload->object, 5, 12, 0, task);
        payload->later_timeline_task = func_080D4704((const void *)0x08948684,
                                                    task);
        descriptor->phase++;
        break;
    case 0x103:
        payload->later_timeline_task = func_080D4774(payload->later_timeline_task);
        if (payload->later_timeline_task)
            break;
        {
            void *object_task;

            object_task = func_080DBA5C(payload->object_task);
            payload->object_task = object_task;
            if (object_task)
                break;
            func_080D45D0((const void *)0x088E9DD8, 6, 0, 0, 1);
            func_080D7220((const void *)0x088F46E4, 1, 3,
                payload->x, payload->y, (u32)object_task);
        }
        payload->timeline_task = func_080D4704((const void *)0x08948D38, task);
        payload->resource_task = func_080D3E9C((const void *)0x0894D6D4, task);
        func_080D3F84(payload->resource_task, 8, 255);
        {
            u32 mask = func_080035A8(3);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        descriptor->phase++;
        break;
    case 0x104:
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        payload->object_task = func_080DBB14(payload->object, 8, 12, 0, task);
        payload->later_timeline_task = func_080D4704((const void *)0x0894AD30,
                                                    task);
        descriptor->phase++;
        break;
    case 0x105:
        payload->later_timeline_task = func_080D4774(payload->later_timeline_task);
        if (payload->later_timeline_task)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task)
            break;
        descriptor->phase++;
        break;
    case 0x106:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
