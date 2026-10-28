/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F2574.c
 * Original SHA-256: 6931896d0a780d01a8bdf888118f86f09391841121b0d0ba9ffd1e88bcff8ab8
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
} Descriptor080F2574;

typedef struct {
    s16 x;
    s16 y;
    u32 unknown_04;
    u32 unknown_08;
    u32 unknown_0c;
    void *coordinate_task;
    void *timeline_task;
    void *child_task;
    u32 copied_input;
    void *result;
} Payload080F2574;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 count,
                          void *output, const void *resource, void *parent);
extern void func_080D7220(const void *resource, u8 index, u8 layer,
                          s16 x, s16 y, u16 flags);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void func_080D3F84(void *task, u8 first, u8 second);
extern void *func_080D4704(const void *resource, void *parent);
extern void func_080D47DC(void *task, u16 value);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 third,
                          u16 fourth, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D4774(void *task);
extern void *func_080D6134(void *task);

/* Target: complete [0x080F2574, 0x080F267E), 266 bytes.
 * 70b584b0061c0d1c141c298880204000814214d0814202dc002909d070e0034881424dd00130814268d069e0010100006868e061782020806020608060e00021605e0222a15e02220092221c08320192164a0292039600220123e3f763fd206113488021009100210191012103227823e4f71cfe0f48311ce1f756fc60610821ff22e1f7c5fc0c48311ce2f781f8a0610721e2f7e9f809480096022104220023edf7bafb20622888013028e09ca739084c5b8f08e0da9408b0b39408b8a839086069e1f767fc6061002819d1a069e2f797f8a061002813d1032010f7abff064a1188814311802069e3f76afd2061002806d12888013002e04009000302202880002004b070bc02bc0847
 */
u32 func_080F2574(void *task, Descriptor080F2574 *descriptor,
                  Payload080F2574 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->copied_input = descriptor->input;
        payload->x = 120;
        payload->y = 96;
        break;
    case 0x100:
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, &payload->unknown_08, (const void *)0x0839A79C, task);
        func_080D7220((const void *)0x088F5B4C, 1, 3, 120, 128, 0);
        payload->timeline_task = func_080D3E9C((const void *)0x0894DAE0, task);
        func_080D3F84(payload->timeline_task, 8, 0xFF);
        payload->child_task = func_080D4704((const void *)0x0894B3B0, task);
        func_080D47DC(payload->child_task, 7);
        payload->result = func_080DFD8C((const void *)0x0839A8B8,
                                      2, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->timeline_task = func_080D3F08(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->child_task = func_080D4774(payload->child_task);
        if (payload->child_task)
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
