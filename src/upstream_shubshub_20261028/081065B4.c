/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081065B4.c
 * Original SHA-256: f8743ce2b7c6931c4a63b797490357345c6cad0f1bf5a87245b70757d318b281
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x081065B4..0x08106778: 452 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 option;
} SequenceEvent;

typedef struct {
    u16 timer;
    u8 option;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *screen;
    u8 unknown_10[8];
    void *effect;
    void *resource;
    void *intro;
    void *actor;
    void *animation;
    void *auxiliary;
} SequenceWork;

extern const u8 data_083A0488[];
extern const u8 data_083A04B8[];
extern const u8 data_083A04E8[];
extern const u8 data_083A04FC[];
extern const u8 data_088ED3F0[];
extern const u8 data_0894D6B4[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080DF8CC(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

int func_081065B4(void *parent, SequenceEvent *event, SequenceWork *work)
{
    void *object;
    u8 mode;

    switch (event->state) {
    case 0:
        work->option = event->option;
        work->actor = event->actor;
        mode = 4;
        if (work->option)
            mode = 0;
        work->intro = func_080E03F8(work->actor, data_083A0488,
            mode, 1, 0, parent);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->intro = func_080E05DC(work->intro);
        if (work->intro)
            break;
        if (!func_080D8858(work->actor, 0)) {
            event->state = 2;
            break;
        }
        object = func_080DD4A4(work->actor, 0);
        work->coordinate_result = func_080DD748(object, &work->x, &work->y, 0);
        work->effect = func_080D6098(work->x, work->y, 0, 1, 2,
            work->unknown_10, data_083A04B8, parent);
        work->animation = func_080DCFE4(object, data_083A04E8, 12, 100, 4, parent, 100);
        work->auxiliary = func_080DFD8C(data_083A04FC, 3, 4, 0, parent);
        work->timer = 30;
        event->state++;
        break;
    case 0x101:
        if (--work->timer)
            break;
        func_080D49FC(0, 2, 0, work->x, work->y);
        work->screen = func_080D4B64(0, data_088ED3F0, 0x3AF, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        work->resource = func_080D3E9C(data_0894D6B4, parent);
        work->timer = 16;
        event->state++;
        break;
    case 0x102:
        if (work->timer) {
            if (--work->timer)
                break;
            func_080DF8CC(work->coordinate_result);
        }
        work->resource = func_080D3F08(work->resource);
        if (work->resource)
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
        work->animation = func_080DBA5C(work->animation);
        if (work->animation)
            break;
        event->state = 2;
        break;
    }
    return 0;
}
