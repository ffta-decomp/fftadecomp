/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08105044.c
 * Original SHA-256: e57c2527e7ec9e28edb50d203fd5ea23768ea15cf090006f25b8c5d56630437f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* Target: complete [0x08105044, 0x0810519E), 346 bytes, 148 instructions.
 * These local offset views do not establish original storage extents or types.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor08105044;

typedef struct {
    u16 countdown;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *coordinate_result;
    u8 unknown_0c[20];
    void *coordinate_task;
    void *initial_task;
    void *actor;
    void *object_task;
    void *output_task;
} Payload08105044;

extern const u8 data_0839F7E4[];
extern const u8 data_0839F808[];
extern const u8 data_0839F880[];
extern const u8 data_0839F890[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD73C(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD580(void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DF860(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08105044(void *task, Descriptor08105044 *descriptor,
                  Payload08105044 *payload)
{
    void *actor;
    void *object;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 3;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(actor, data_0839F7E4,
            mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object,
            &payload->x, &payload->y, 0);
        if (func_080DD73C(payload->coordinate_result) != 0)
            payload->y -= 8;
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 5, payload->unknown_0c, data_0839F808, task);
        payload->object_task = func_080DCFE4(object, 0, 12, 0, 2, task, 50);
        payload->output_task = func_080DFD8C(data_0839F880, 2, 4, 0, task);
        if (func_080DD580(object) != 0) {
            payload->output_task = func_080DFD8C(data_0839F890,
                1, 12, 50, task);
            payload->countdown = 30;
        }
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown == 0)
                func_080DF860(func_080DD4B4(payload->actor, 0));
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
