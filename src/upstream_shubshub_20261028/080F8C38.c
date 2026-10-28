/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080F8C38.c
 * Original SHA-256: da84c0c268b6e2492cbf58c28765c2a7b74af8beded4fd02837bdb40b19d4c07
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target [0x080F8C38, 0x080F8E3A), 514 bytes. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    u16 selector;
    u16 mode;
} Descriptor080F8C38;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 mode;
    u8 ready;
    u32 unknown_08;
    void *object;
    void *coordinate_result;
    void *selected_object;
    void *source;
    void *initial_child;
    u32 unknown_20[3];
    void *coordinate_child;
    void *effect_child;
    void *object_child;
    void *animation_child;
    void *record_child;
} Payload080F8C38;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DF9E4(void *, u16, u16, void *);
extern void *func_080DBA5C(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);

u32 func_080F8C38(void *task, Descriptor080F8C38 *descriptor,
                  Payload080F8C38 *payload)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->source = descriptor->object;
        mode = 2;
        if (payload->mode != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->source,
            (const void *)0x0839C230, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->source)) {
            descriptor->phase = 2;
            break;
        }
        payload->animation_child = func_080DDF68(payload->source,
            &payload->object, 0x8007, 2, &payload->ready,
            (const void *)0x0839C2A4, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DBFFC(payload->source, 0);
        payload->countdown = 4;
        descriptor->phase++;
    case 0x102:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        if (func_080D8B4C())
            break;
        if (func_080D8858(payload->source, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->selected_object = func_080DD4A4(payload->source, 0);
        payload->coordinate_result = func_080DD748(payload->selected_object,
            &payload->x, &payload->y, 0);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_20, (const void *)0x0839C248, task);
        payload->effect_child = func_080D4704((const void *)0x0894ABF0, task);
        payload->record_child = func_080DFD8C((const void *)0x0839C2AC,
            3, 4, 0, task);
        payload->countdown = 24;
        descriptor->phase++;
        break;
    case 0x103:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        payload->object_child = func_080DF9E4(payload->selected_object, 11, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child != 0)
            break;
        payload->object_child = func_080DCFE4(payload->selected_object,
            (const void *)0x0839C290, 12, 0, 12, task, 0);
        descriptor->phase++;
        break;
    case 0x105:
        if (func_080DE1F0(payload->object) == 0)
            break;
        payload->effect_child = func_080D4774(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
