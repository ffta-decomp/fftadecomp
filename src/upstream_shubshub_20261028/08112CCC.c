/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08112CCC.c
 * Original SHA-256: 69b888f98b56cb2d7b04452264a751cb9ee3739d3a248ef8756ad2911e909514
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: complete [0x08112CCC, 0x08112E86), 442 bytes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 counter;
    u16 index;
    u32 unknown_04;
    void *first_object;
    void *second_object;
    struct InterpolationState motion;
    void *record_task;
};

extern const u8 data_08505D34[];
extern const u8 data_08505D4C[];
extern const u8 data_083A37A0[];
extern const s16 data_083A35C0[];

extern void *func_080D5CC0(const void *, int, int, int, int, int, int, int);
extern void func_08011058(void *, int);
extern void func_080110F8(void *, int);
extern void func_080112E8(void *, int);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E064C(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, s16);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080112CC(void *, s16, s16, u16);
extern void func_08011428(void *);

u32 func_08112CCC(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
    case 1:
        break;
    case 0x100:
        payload->first_object = func_080D5CC0(data_08505D34, 0, 120, -8,
                                             660, 7, 0, 0);
        payload->second_object = func_080D5CC0(data_08505D4C, 0, 120, 128,
                                              658, 8, 0, 0);
        func_08011058(payload->first_object, 1);
        func_080110F8(payload->first_object, 1);
        func_080112E8(payload->first_object, 1);
        func_080E0608(&payload->motion, -8, 32, 29);
        payload->record_task = func_080DFD8C(data_083A37A0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->motion);
        func_080107D4(payload->first_object, 120, payload->motion.current, 0);
        if (func_080E0690(&payload->motion)) {
            payload->counter = 20;
            descriptor->phase++;
        }
        break;
    case 0x102:
        func_080112CC(payload->first_object, data_083A35C0[payload->index],
                     data_083A35C0[payload->index], 0);
        payload->index++;
        if (--payload->counter == 0) {
            func_080E0608(&payload->motion, 32, 112, 39);
            descriptor->phase++;
        }
        break;
    case 0x103:
        func_080E064C(&payload->motion);
        func_080107D4(payload->first_object, 120, payload->motion.current, 0);
        func_080112CC(payload->first_object, data_083A35C0[payload->index],
                     data_083A35C0[payload->index], 0);
        payload->index++;
        if (func_080E0690(&payload->motion)) {
            func_08011428(payload->first_object);
            payload->first_object = 0;
            func_08011428(payload->second_object);
            payload->second_object = 0;
            descriptor->phase++;
        }
        break;
    case 0x104:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
