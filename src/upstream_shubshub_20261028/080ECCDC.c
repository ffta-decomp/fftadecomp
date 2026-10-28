/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080ECCDC.c
 * Original SHA-256: e22f63f8915ce518cda16773eeae7f7c9a778aa295530020b5ab70e5008701ff
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target 0x080ECCDC, complete [0x080ECCDC, 0x080ECD8C), 176 bytes:
 * f0b584b0161c0988012906d0012947dd8020400081422bd042e0301d0821e9f73bf93de0381c0821e9f74ef9051c2d042d0c0e486178a278e378ee24a400009407240194002402940394e8f7cbff2d04ad137d192860718849420904091424f78df970880130708017e00000c4cb4f08341d201c0821e9f7e7f87188271c2b290bd80a4b32888800c41820788242c9d0481c0004010c2b29f5d9308801303080002004b0f0bc02bc084700008c913908
 */

typedef struct {
    u16 phase;
} Descriptor080ECCDC;

typedef struct {
    u8 time;
    u8 kind;
    u8 x;
    u8 y;
} Event080ECCDC;

typedef struct {
    u16 counter;
    u16 created;
    void *slots[8];
} Payload080ECCDC;

extern void func_080D5F74(void **slots, u16 count);
extern u32 func_080D5F24(void **slots, u16 count);
extern s16 func_080D5FA4(void **slots, u16 count);
extern void *func_080D5CC0(const void *resource, u16 kind, s16 x, s16 y,
                          s16 value, u8 first, u8 second, u8 third);
extern void func_08011058(void *object, s16 value);
extern const Event080ECCDC g_table_0839918C[];

u32 func_080ECCDC(void *task, Descriptor080ECCDC *descriptor,
                  Payload080ECCDC *payload)
{
    const Event080ECCDC *events;
    const Event080ECCDC *event;
    u16 index;
    u16 slot;
    void *object;

    switch (descriptor->phase) {
    case 0:
        break;
    case 1:
        func_080D5F74(payload->slots, 8);
        break;
    case 0x100:
        func_080D5F24(payload->slots, 8);
        for (index = payload->created; index < 44; index++) {
            events = g_table_0839918C;
            event = &events[index];
            if (payload->counter == event->time) {
                slot = func_080D5FA4(payload->slots, 8);
                object = func_080D5CC0((const void *)0x084FCBC4,
                                     event->kind, event->x, event->y,
                                     0x3B8, 7, 0, 0);
                payload->slots[(s16)slot] = object;
                func_08011058(object, -payload->created);
                payload->created++;
                break;
            }
        }
        payload->counter++;
        break;
    }
    return 0;
}
