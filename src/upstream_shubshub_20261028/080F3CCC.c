/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F3CCC.c
 * Original SHA-256: e0a4a9ea0b71c815e68391b3a0515011b9dcd46a9c0194182624f56bfbdd0a15
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080F3CCC..0x080F3E7A: 430 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    s16 kind;
    u16 option;
} SequenceEvent;

typedef struct {
    s16 x;
    s16 y;
    u8 kind;
    u8 option;
    u8 ready;
    u8 unknown_07;
    void *output;
    u32 coordinate_result;
    void *actor;
    void *intro;
    u8 unknown_18[8];
    void *effect;
    void *animation;
    void *output_task;
    void *auxiliary;
} SequenceWork;

typedef struct {
    u8 unknown_00[20];
} AnimationDescriptor;

extern const void *const data_0839AE74[];
extern const u8 data_0839AED4[];
extern const u8 data_0839AE7C[];
extern const AnimationDescriptor data_0839AEAC[];
extern const u8 data_0839AEDC[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern u8 func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DE1F0(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

int func_080F3CCC(void *parent, SequenceEvent *event, SequenceWork *work)
{
    void *object;
    u8 mode;

    switch (event->state) {
    case 0:
        if (event->kind == 0x53)
            work->kind = 0;
        else
            work->kind = 1;
        work->option = event->option;
        work->actor = event->actor;
        mode = 3;
        if (work->option)
            mode = 0;
        work->intro = func_080E03F8(work->actor, data_0839AE74[work->kind],
            mode, 0, 0, parent);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->intro = func_080E05DC(work->intro);
        if (work->intro)
            break;
        if (func_080D3B54(work->actor)) {
            event->state = 2;
            break;
        }
        work->output_task = func_080DDF68(work->actor, &work->output,
            0x8007, 2, &work->ready, data_0839AED4, 0x15, 0, parent);
        event->state++;
        break;
    case 0x101:
        if (!work->ready)
            break;
        func_080DC12C(work->actor, 0, 2);
        event->state++;
    case 0x102:
        if (func_080D8B4C())
            break;
        if (!func_080D8858(work->actor, 0)) {
            event->state = 2;
            break;
        }
        object = func_080DD4A4(work->actor, 0);
        work->coordinate_result = func_080DD748(object, &work->x, &work->y, 0);
        work->effect = func_080D6098(work->x, work->y, 0, 1, 2,
            work->unknown_18, data_0839AE7C, parent);
        work->animation = func_080DCFE4(object, &data_0839AEAC[work->kind],
            12, 15, 4, parent, 40);
        work->auxiliary = func_080DFD8C(data_0839AEDC, 1, 4, 0, parent);
        event->state++;
        break;
    case 0x103:
        if (!func_080DE1F0(work->output))
            break;
        work->effect = func_080D6134(work->effect);
        if (work->effect)
            break;
        work->animation = func_080DBA5C(work->animation);
        if (work->animation)
            break;
        event->state = 2;
        break;
    }
    return 0;
}
