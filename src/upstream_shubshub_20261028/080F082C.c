/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F082C.c
 * Original SHA-256: c32eb9b7f9bbd555afc4691051dc56ce37066f71d505dd9f6e3a2fa3776e9808
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080F082C..0x080F0ABE: 658 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0x0C];
    u8 kind;
    u8 unknown_15;
    u16 option;
} SequenceEvent;

typedef struct {
    u8 kind;
    u8 option;
    u8 toggle;
    u8 unknown_03[5];
    void *panel;
    u32 effect_state;
    void *effect;
    void *opening;
    void *animation;
    void *closing;
    void *cleanup;
    void *final_task;
    void *object;
    void *intro;
    void *auxiliary;
} SequenceWork;

extern const u8 data_0839A378[];
extern const void *const data_0839A358[];
extern const u8 data_0839A380[];
extern const u8 data_0839A398[];
extern const u8 data_0839A3A0[];
extern const u8 data_0839A3B8[];
extern void *func_080E03F8(void *object, const void *descriptor, int mode,
                           int priority, int option, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *object);
extern void *func_080F1184(u8 kind, void **panel, void *parent);
extern void *func_080F1210(void *task);
extern void *func_080F1DEC(u8 kind, void *object, void *parent);
extern void func_08011138(void *panel, u8 value);
extern u16 func_08005BAC(const void *object);
extern void func_0801121C(void *panel, s16 value);
extern void func_08011014(void *panel, u8 value);
extern void *func_080D6098(s16 x, s16 y, int layer, int enabled,
                           int mode, void *state, const void *descriptor,
                           void *parent);
extern void *func_080DFD8C(const void *descriptor, int first, int second,
                           int third, void *parent);
extern void func_080D620C(void *object, s16 value);
extern u8 func_08010FF0(void *panel);
extern void *func_080D6134(void *task);
extern void *func_080F2E40(u8 kind, void *object, void *parent);
extern void *func_080F11A8(u8 kind, void **panel, void *parent);
extern void func_08011428(void *panel);
extern void *func_080DD47C(void *object);
extern void func_080DE390(void *object);
extern u8 func_080D8858(void *object, int mode);
extern void *func_080F11CC(void *object, u8 kind, void *parent);

static inline void toggle_panel(SequenceWork *work)
{
    u8 toggle = work->toggle;

    func_08011138(work->panel, toggle);
    work->toggle = !toggle;
}

int func_080F082C(void *parent, SequenceEvent *event, SequenceWork *work)
{
    u8 intro_mode;

    switch (event->state) {
    case 0:
        work->kind = event->kind - 0x42;
        work->option = event->option;
        work->object = event->object;
        intro_mode = data_0839A378[work->kind];
        if (work->option)
            intro_mode = 0;
        work->intro = func_080E03F8(work->object,
                                     data_0839A358[work->kind],
                                     intro_mode, 5, 0, parent);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->intro = func_080E05DC(work->intro);
        if (!work->intro) {
            if (work->option) {
                event->state = 0x105;
            } else {
                work->opening = func_080F1184(work->kind, &work->panel, parent);
                event->state++;
            }
        }
        break;
    case 0x101:
        work->opening = func_080F1210(work->opening);
        if (!work->opening) {
            work->animation = func_080F1DEC(work->kind, work->object, parent);
            event->state++;
        }
        break;
    case 0x102:
        toggle_panel(work);
        if (work->kind != 7) {
            work->animation = func_080F1210(work->animation);
            if (work->animation)
                break;
        } else {
            if (func_08005BAC(work->animation) != 0x104)
                break;
        }
        func_0801121C(work->panel, 0);
        func_08011014(work->panel, 1);
        if (work->kind == 6) {
            work->effect = func_080D6098(0x78, 0x38, 0, 1, 1,
                                          &work->effect_state,
                                          data_0839A380, parent);
            work->auxiliary = func_080DFD8C(data_0839A398, 1, 4, 0, parent);
        } else if (work->kind == 7) {
            work->effect = func_080D6098(0x78, 0x80, 0, 1, 1,
                                          &work->effect_state,
                                          data_0839A3A0, parent);
            func_080D620C(work->effect, -1);
            work->auxiliary = func_080DFD8C(data_0839A3B8, 1, 4, 0, parent);
        }
        event->state++;
        break;
    case 0x103:
        work->animation = func_080F1210(work->animation);
        if (work->animation)
            break;
        if (!func_08010FF0(work->panel))
            break;
        work->effect = func_080D6134(work->effect);
        if (work->effect)
            break;
        work->closing = func_080F2E40(work->kind, work->object, parent);
        event->state++;
        break;
    case 0x104:
        toggle_panel(work);
        work->closing = func_080F1210(work->closing);
        if (!work->closing) {
            work->cleanup = func_080F11A8(work->kind, &work->panel, parent);
            event->state++;
        }
        break;
    case 0x105:
        work->cleanup = func_080F1210(work->cleanup);
        if (!work->cleanup) {
            func_08011428(work->panel);
            work->panel = 0;
            func_080DE390(func_080DD47C(work->object));
            if (func_080D8858(work->object, 0)) {
                work->final_task = func_080F11CC(work->object, work->kind, parent);
                event->state++;
            } else {
                event->state = 2;
            }
        }
        break;
    case 0x106:
        work->final_task = func_080F1210(work->final_task);
        if (!work->final_task)
            event->state++;
        break;
    case 0x107:
        event->state = 2;
        break;
    }
    return 0;
}
