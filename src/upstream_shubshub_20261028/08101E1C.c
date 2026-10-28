/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08101E1C.c
 * Original SHA-256: 793e1c611703606cbf8d3a40fc557be1a9ee71a71034b70c2e627b67e010fc31
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08101E1C..0x0810205C: 576 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 option;
} SequenceEvent;

typedef struct {
    u16 unknown_00;
    u8 option;
    u8 status;
    s16 x;
    s16 y;
    void *status_task;
    void *actor_object;
    void *coordinate_result;
    void *selected_object;
    void *effect;
    u32 effect_state;
    void *screen;
    void *resource;
    void *timeline;
    void *actor;
    void *intro;
    void *secondary;
    void *animation;
    void *auxiliary;
} SequenceWork;

extern const u8 data_0839EE60[];
extern const u8 data_0839EE84[];
extern const u8 data_088EF35C[];
extern const u8 data_0894D900[];
extern const u8 data_0894AD94[];
extern const u8 data_0839EE9C[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_08102B48(void *, u8, u8 *, void *);
extern void *func_080DD47C(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DBB14(void *, u8, u16, u16, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DBA5C(void *);
extern u8 func_080DD580(void *);
extern s8 func_080DBC88(void *);
extern void *func_080DF7A0(void *, u8, u8, u8, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D6134(void *);
extern void *func_08102BA8(void *);

int func_08101E1C(void *parent, SequenceEvent *event, SequenceWork *work)
{
    u8 mode;

    switch (event->state) {
    case 0:
        work->option = event->option;
        work->actor = event->actor;
        mode = 3;
        if (work->option)
            mode = 0;
        work->intro = func_080E03F8(work->actor, data_0839EE60,
            mode, 0, 0, parent);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->intro = func_080E05DC(work->intro);
        if (work->intro)
            break;
        work->status_task = func_08102B48(work->actor, 4, &work->status, parent);
        if (!work->status_task) {
            event->state = 2;
            break;
        }
        event->state++;
        break;
    case 0x101:
        if (!work->status)
            break;
        if (work->status == 2) {
            event->state = 0x103;
            break;
        }
        work->actor_object = func_080DD47C(work->actor);
        work->selected_object = func_080DD4A4(work->actor, 0);
        work->coordinate_result = func_080DD748(work->selected_object,
            &work->x, &work->y, 0);
        work->effect = func_080D6098(work->x, work->y, 0, 1, 1,
            &work->effect_state, data_0839EE84, parent);
        func_080D49FC(0, 2, 0, work->x, work->y);
        work->screen = func_080D4B64(0, data_088EF35C, 0x3E6, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        work->resource = func_080D3E9C(data_0894D900, parent);
        work->timeline = func_080D4704(data_0894AD94, parent);
        work->animation = func_080DBB14(work->coordinate_result, 4, 12, 0, parent);
        work->auxiliary = func_080DFD8C(data_0839EE9C, 2, 4, 0, parent);
        event->state++;
        break;
    case 0x102:
        work->animation = func_080DBA5C(work->animation);
        if (work->animation)
            break;
        if (func_080DD580(work->selected_object)) {
            u8 property = func_080DBC88(work->coordinate_result);
            work->secondary = func_080DF7A0(work->coordinate_result,
                6, property > 1 ? 1 : 0, 4, 0, parent);
        }
        work->animation = func_080DCFE4(work->selected_object, 0, 12, 0, 4, parent, 0);
        event->state++;
        break;
    case 0x103:
        work->resource = func_080D3F08(work->resource);
        if (work->resource)
            break;
        work->timeline = func_080D4774(work->timeline);
        if (work->timeline)
            break;
        work->screen = func_080D4D2C(work->screen, 0);
        if (work->screen)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        work->effect = func_080D6134(work->effect);
        if (work->effect)
            break;
        work->status_task = func_08102BA8(work->status_task);
        if (work->status_task)
            break;
        work->animation = func_080DBA5C(work->animation);
        if (work->animation)
            break;
        work->secondary = func_080DBA5C(work->secondary);
        if (work->secondary)
            break;
        event->state = 2;
        break;
    }
    return 0;
}
