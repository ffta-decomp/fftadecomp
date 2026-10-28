/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081195F8.c
 * Original SHA-256: c40830b7b97f3af4e2f20dd59d55a5343275d8394e9f697622d61f66aed3f121
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x081195F8, 0x08119914), 796 bytes, 340 instructions.
 * Local offset views; original declarations and full extents are unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 variant;
} Descriptor081195F8;

typedef struct {
    s16 x;
    s16 y;
    u8 variant;
    u8 count;
    u8 index;
    u8 delay;
    u16 countdown;
    u8 ready;
    u8 unknown_0b;
    void *scripted_child;
    void *object;
    u8 coordinate_output[8];
    void *coordinate_child;
    void *sprite;
    void *timeline;
    void *window_child;
    void *actor;
    void *initial_child;
    void *wrapper_child;
    void *children[4];
    void *record_child;
} Payload081195F8;

extern const u8 data_083A6348[];
extern const u8 data_083A63A8[];
extern const u8 data_088EF398[];
extern const u8 data_0894D90C[];
extern const u8 data_083A6390[];
extern const u8 data_0894AAB0[];
extern const u8 data_083A63C0[];
extern const u8 data_083A63AC[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern void *func_080DD47C(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080F2E40(u8, void *, void *);
extern void *func_080F1210(void *);
extern u8 func_080D8858(void *, u16);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_081195F8(void *task, Descriptor081195F8 *descriptor,
                  Payload081195F8 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 animation;

            payload->variant = descriptor->variant;
            payload->actor = descriptor->actor;
            animation = 6;
            if (payload->variant != 0)
                animation = 0;
            payload->initial_child = func_080E03F8(payload->actor,
                data_083A6348, animation, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        if (payload->variant != 0) {
            payload->count = func_080DD494(payload->actor);
            payload->delay = 1;
            descriptor->phase = 0x103;
            break;
        }
        payload->wrapper_child = func_080DDF68(payload->actor,
            &payload->object, 88, 1, &payload->ready,
            data_083A63A8, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->object = func_080DD47C(payload->actor);
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        func_080D49FC(1, 3, 0, payload->x, payload->y);
        payload->sprite = func_080D4B64(1, data_088EF398, 703, 6);
        {
            u32 mask = func_080035A8(3);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->timeline = func_080D3E9C(data_0894D90C, task);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->coordinate_output, data_083A6390, task);
        payload->window_child = func_080D4724(data_0894AAB0, task, 15);
        payload->record_child = func_080DFD8C(data_083A63C0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->sprite = func_080D4D2C(payload->sprite, 1);
        if (payload->sprite != 0)
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->window_child = func_080D4774(payload->window_child);
        if (payload->window_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        func_080DE3BC(payload->object, 0);
        func_080DBA50(payload->wrapper_child);
        payload->scripted_child = func_080F2E40(9, payload->actor, task);
        descriptor->phase++;
        break;
    case 0x103:
        payload->scripted_child = func_080F1210(payload->scripted_child);
        if (payload->scripted_child != 0)
            break;
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        payload->count = func_080D8858(payload->actor, 0);
        if (payload->count == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->delay = 1;
        descriptor->phase++;
        break;
    case 0x104:
        func_080DBFFC(payload->actor, payload->index);
        descriptor->phase++;
    case 0x105:
        if (func_080D8B4C())
            break;
        payload->delay--;
        if (payload->delay != 0)
            break;
        {
            void *object;
            s32 parity;
            u16 flags;

            object = func_080DD4A4(payload->actor, payload->index);
            parity = payload->index & 1;
            flags = 2;
            if (parity != 0)
                flags = 4;
            payload->children[payload->index] = func_080DCFE4(object,
                data_083A63AC, 12 - parity, 0, flags | 8, task, 0);
        }
        payload->delay = 40;
        payload->index++;
        if (payload->index != payload->count)
            descriptor->phase = 0x104;
        else
            descriptor->phase++;
        break;
    case 0x106:
        if (func_080DE1F0(payload->object)) {
            u8 done = 1;
            u8 index;

            for (index = 0; index < 4; index++) {
                payload->children[index] = func_080DBA5C(payload->children[index]);
                if (payload->children[index] != 0)
                    done = 0;
            }
            if (done)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
