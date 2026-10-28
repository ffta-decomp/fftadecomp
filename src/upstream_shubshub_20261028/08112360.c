/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08112360.c
 * Original SHA-256: 329ffa10879c577d46196dbfaa7e792389ad92f8584c30ea52b6c2f907cbbde5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

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
    u8 unknown_02[6];
    void *object;
    void *child;
    struct InterpolationState scanline;
    struct InterpolationState y_motion;
    void *scanline_task;
};

extern const u8 data_083A34D8[];
extern const u8 data_08504D8C[];
extern u16 g_control_flags_03000940;
extern void *func_080D9914(u16, u16, void *);
extern u16 func_080D499C(u16, u16);
extern u16 *func_080D996C(void *);
extern void func_080D9BA8(void *, u8);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern u32 func_080D3904(void);
extern void func_0801DCB8(u32);
extern void func_080107D4(void *, s16, s16, u8);
extern void func_08011428(void *);
extern u32 func_080035A8(u8);
extern void *func_080D9B64(void *);
extern void *func_080D3F08(void *);

/* Target: complete [0x08112360, 0x08112592), 562 bytes, 240 instructions. */
u32 func_08112360(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        void *scanline_task = func_080D9914(2, 1, task);
        u16 value = func_080D499C(2, 1);
        u16 *buffer = func_080D996C(scanline_task);
        u16 i;

        for (i = 0; i < 160; i++)
            buffer[i] = value;
        func_080D9BA8(scanline_task, 1);
        payload->scanline_task = scanline_task;
        func_080E0608(&payload->scanline, 0, 160, 8);
        break;
    }
    case 0x100: {
        u16 *buffer;
        u8 i;
        s16 value;

        func_080E064C(&payload->scanline);
        buffer = func_080D996C(payload->scanline_task);
        for (i = 0; i < 160 && i != 160 - payload->scanline.current; i++)
            buffer[i] = payload->scanline.current;
        value = payload->scanline.current;
        for (; i < 160; i++) {
            buffer[i] = value;
            value--;
        }
        if (func_080E0690(&payload->scanline)) {
            func_080E0608(&payload->scanline, 160, 168, 48);
            payload->child = func_080D3E9C(data_083A34D8, task);
            func_080E0608(&payload->y_motion, 172, -12, 32);
            payload->object = func_080D5CC0(data_08504D8C, 3, 120,
                                           payload->y_motion.current, 779, 8, 0, 0);
            func_0801DCB8(func_080D3904() + 192);
            descriptor->phase++;
        }
        break;
    }
    case 0x101: {
        u16 *buffer;
        s16 value;
        u8 i;

        func_080E064C(&payload->scanline);
        buffer = func_080D996C(payload->scanline_task);
        value = payload->scanline.current;
        for (i = 0; i < 160; i++) {
            buffer[i] = value;
            value--;
        }
        func_080E064C(&payload->y_motion);
        if (payload->object != 0) {
            u32 cycle = payload->counter & 3;
            s16 x = 120;
            s16 y = payload->y_motion.current;

            if (cycle == 1)
                y += 2;
            else if (cycle == 3)
                y -= 2;
            payload->counter++;
            func_080107D4(payload->object, x, y, 0);
            if (func_080E0690(&payload->y_motion)) {
                func_08011428(payload->object);
                payload->object = 0;
            }
        }
        if (func_080E0690(&payload->scanline)) {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
            descriptor->phase++;
        }
        break;
    }
    case 0x102:
        payload->scanline_task = func_080D9B64(payload->scanline_task);
        if (payload->scanline_task == 0) {
            payload->child = func_080D3F08(payload->child);
            if (payload->child == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
