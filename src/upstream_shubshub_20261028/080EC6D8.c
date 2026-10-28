/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EC6D8.c
 * Original SHA-256: b9cc9dbf7ed453664981031fcf320e0a09f395616c1a2e4e8ff3507d6f3adfed
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x080EC6D8 .. 0x080EC7DC: 260 target bytes, including literal pools. */
#include "ffta.h"

typedef struct {
    u16 phase;
} Descriptor080EC6D8;

typedef struct {
    s16 x;
    s16 initial_y;
    s32 fixed_y;
} Record080EC6D8;

typedef struct {
    u16 counter;
    u16 unknown_02;
    void *slots[12];
    Record080EC6D8 records[12];
} Payload080EC6D8;

typedef struct {
    u16 time;
    u8 kind;
    u8 order;
    u8 x;
    u8 y;
    s16 velocity;
} Event080EC6D8;

extern Event080EC6D8 g_events_083990EC[];

extern void func_080D5F74(void **slots, u16 count);
extern void *func_080D5CC0(const void *resource, u16 kind, s16 x, s16 y,
                         s16 depth, u8 a6, u8 a7, u8 a8);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);
extern void func_08011058(void *object, s16 order);

u32 func_080EC6D8(void *task, Descriptor080EC6D8 *descriptor,
                  Payload080EC6D8 *payload)
{
    u16 index;

    switch (descriptor->phase) {
    case 0:
        break;
    case 1:
        func_080D5F74(payload->slots, 12);
        break;
    case 0x100:
        for (index = 0; index < 12; index++) {
            if (payload->slots[index] != 0) {
                payload->records[index].fixed_y += g_events_083990EC[index].velocity;
                if (payload->records[index].fixed_y < -4096) {
                    payload->records[index].x =
                        (payload->records[index].x + 30) & 255;
                    payload->records[index].fixed_y =
                        payload->records[index].initial_y << 8;
                }
                func_080107D4(payload->slots[index], payload->records[index].x,
                    (s16)(payload->records[index].fixed_y >> 8), 0);
            } else if (payload->counter == g_events_083990EC[index].time) {
                payload->records[index].x = g_events_083990EC[index].x;
                payload->records[index].initial_y = g_events_083990EC[index].y;
                payload->records[index].fixed_y = g_events_083990EC[index].y << 8;
                payload->slots[index] = func_080D5CC0((const void *)0x084F71D8,
                    g_events_083990EC[index].kind,
                    g_events_083990EC[index].x, g_events_083990EC[index].y,
                    0x3CC, 6, 0, 0);
                func_08011058(payload->slots[index], g_events_083990EC[index].order);
            }
        }
        payload->counter++;
        break;
    }
    return 0;
}
