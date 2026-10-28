/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080FBC1C.c
 * Original SHA-256: 6b5d4745562047b0edbcc90cde747401d18ce606d093467400ffb402a51fdc8a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x080FBC1C, complete [0x080FBC1C, 0x080FBEA0), 644 bytes. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080FBC1C;

typedef struct {
    s16 x;
    s16 y;
    u16 counter;
    u8 flag;
    u8 ready;
    void *output;
    void *coordinate_result;
    void *actor;
    void *initial_child;
    void *record_child;
    void *timed_child;
    void *effect_child;
    void *output_child;
    void *final_child;
} Payload080FBC1C;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D73AC(const void *, u8, u8, s16, s16, u8);
extern u16 func_080035A8(u8);
extern void func_08003620(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080DCFE4(void *, const void *, u8, s16, s16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D6E30(const void *, u8, s16, s16, s16, s16, s16);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern void *func_080DBA5C(void *);
extern const s16 data_0839CF9C[];
extern const s16 data_0839D014[];

u32 func_080FBC1C(void *task, Descriptor080FBC1C *descriptor,
                  Payload080FBC1C *payload)
{
    void *actor_object;
    void *actor;
    u8 animation;
    u8 actor_status;
    u8 busy;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 3;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor,
            (const void *)0x0839CF58, animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        actor_status = func_080D3B54(payload->actor);
        if (actor_status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->output_child = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready,
            (const void *)0x0839CF90, 5, actor_status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DBFFC(payload->actor, 0);
        payload->counter = 30;
        descriptor->phase++;
        /* Fall through: begin the countdown in this invocation. */
    case 0x102:
        if (payload->counter != 0 && --payload->counter != 0)
            break;
        busy = func_080D8B4C();
        if (busy != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        func_080D73AC((const void *)0x088F5AFC, 0, 2,
            payload->x, payload->y, busy);
        *(u16 *)0x03000940 |= func_080035A8(2);
        func_08003620(1);
        payload->record_child = func_080D3E9C((const void *)0x0894DA80, task);
        payload->timed_child = func_080D4724((const void *)0x0894848C, task, 120);
        payload->effect_child = func_080DCFE4(actor_object,
            (const void *)0x0839CF7C, 12, 100, 4, task, 100);
        payload->final_child = func_080DFD8C((const void *)0x0839CF94,
            1, 4, 0, task);
        payload->counter = 60;
        descriptor->phase++;
        break;
    case 0x103:
        if (--payload->counter == 0)
            descriptor->phase++;
        break;
    case 0x104:
        func_080D6E30((const void *)0x088F5AFC, 2, payload->x, payload->y,
            data_0839CF9C[payload->counter],
            data_0839D014[payload->counter], 0);
        if (++payload->counter <= 59)
            break;
        *(u16 *)0x03000940 &= ~func_080035A8(2);
        descriptor->phase++;
        break;
    case 0x105:
        if (func_080DE1F0(payload->output) == 0)
            break;
        payload->timed_child = func_080D4774(payload->timed_child);
        if (payload->timed_child != 0)
            break;
        payload->record_child = func_080D3F08(payload->record_child);
        if (payload->record_child != 0)
            break;
        func_08003620(0);
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
