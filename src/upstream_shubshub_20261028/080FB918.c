/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FB918.c
 * Original SHA-256: 67507d184614c94ad3ba0040463dfaa9f6396db4e9fe1e0d456f17f915cd927f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 0x080FB918..0x080FBC1A (770 bytes). */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    u16 unknown_14;
    u16 flag;
};

struct Payload {
    s16 x;
    s16 y;
    u16 counter;
    u8 flag;
    u8 ready;
    u8 property;
    u8 unknown_09[3];
    void *helper_output;
    void *coordinate_result;
    void *actor;
    void *initial;
    void *first_object;
    void *second_object;
    void *third_object;
    void *effect;
    void *transition;
    void *retained_30;
    void *retained_34;
};

extern const u8 data_0839CEEC[];
extern const u8 data_0839CF10[];
extern const u8 data_0839CF24[];
extern const u8 data_0839CF28[];
extern const u8 data_084FF654[];
extern const u8 data_08502CF0[];
extern const u8 data_08949DD8[];

extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, int, int, u8 *, const void *, int, int, void *);
extern u8 func_080DBFFC(void *, int);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, int);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern s8 func_080DBC88(void *);
extern void *func_080D5CC0(const void *, int, int, int, int, int, int, int);
extern void func_08011058(void *, int);
extern void func_0801121C(void *, int);
extern void func_080111A8(void *, int);
extern void func_08011118(void *, int);
extern void func_08011198(void *);
extern void *func_080DCFE4(void *, const void *, int, int, int, void *, int);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080D5F74(void **, int);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

int func_080FB918(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    u8 busy;
    void *actor_state;

    switch (descriptor->phase) {
    case 0: {
        int mode;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 3;
        if (payload->flag != 0)
            mode = 0;
        payload->initial = func_080E03F8(payload->actor, data_0839CEEC,
                                       mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 blocked;
        payload->initial = func_080E05DC(payload->initial);
        if (payload->initial != 0)
            break;
        blocked = func_080D3B54(payload->actor);
        if (blocked != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->retained_30 = func_080DDF68(payload->actor, &payload->helper_output,
                                            0x8007, 1, &payload->ready,
                                            data_0839CF24, 5, blocked, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DBFFC(payload->actor, 0);
        payload->counter = 30;
        descriptor->phase++;
    case 0x102:
        if (payload->counter != 0) {
            if (--payload->counter != 0)
                break;
        }
        busy = func_080D8B4C();
        if (busy != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_state = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_state, &payload->x,
                                                   &payload->y, 0);
        payload->property = func_080DBC88(payload->helper_output);
        payload->first_object = func_080D5CC0(data_08502CF0, 1, payload->x, payload->y,
                                              992, 6, busy, 1);
        payload->second_object = func_080D5CC0(data_08502CF0, 0, payload->x, payload->y,
                                               992, 6, busy, 1);
        func_08011058(payload->first_object, -2);
        func_0801121C(payload->first_object, -1);
        func_080111A8(payload->second_object, 1);
        if (payload->property > 1) {
            func_08011118(payload->first_object, 1);
            func_08011118(payload->second_object, 1);
        }
        payload->transition = func_080DCFE4(actor_state, data_0839CF10,
                                           12, 56, 4, task, 56);
        payload->retained_34 = func_080DFD8C(data_0839CF28, 2, 4, 0, task);
        payload->counter = busy;
        descriptor->phase++;
        break;
    case 0x103:
        if (++payload->counter <= 5)
            break;
        func_080111A8(payload->second_object, 0);
        descriptor->phase++;
        break;
    case 0x104:
        if (++payload->counter <= 39)
            break;
        payload->third_object = func_080D5CC0(data_084FF654, 1, payload->x, payload->y,
                                              980, 7, 0, 1);
        func_08011058(payload->third_object, -1);
        func_08011198(payload->third_object);
        if (payload->property > 1)
            func_08011118(payload->third_object, 1);
        payload->effect = func_080D4704(data_08949DD8, task);
        descriptor->phase++;
        break;
    case 0x105:
        if (++payload->counter <= 49)
            break;
        func_080111A8(payload->second_object, 1);
        payload->counter = 6;
        descriptor->phase++;
        break;
    case 0x106:
        if (payload->counter != 0) {
            if (--payload->counter != 0)
                break;
            func_080D5F74(&payload->first_object, 3);
        }
        if (func_080DE1F0(payload->helper_output) == 0)
            break;
        payload->effect = func_080D4774(payload->effect);
        if (payload->effect != 0)
            break;
        payload->transition = func_080DBA5C(payload->transition);
        if (payload->transition == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
