/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08009AFC.c
 * Original SHA-256: 8dc5cc5020009be74c757a17be51db87d630d0dfeabf4c4df6fc4f5de9472a2a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 entries[4];
    u8 count;
} EventQueue;

typedef void (*ClearCallback)(void *destination, u32 size);

extern const ClearCallback g_callbacks_0836D4B8[];
extern EventQueue data_02002194;
extern u8 g_state_02000000[];

u8 func_080C9540(u16 bit_index);
void func_080C9574(u16 bit_index, u16 enabled);
void func_080C95C0(u16 index, u32 value);

/* 0x08009AFC .. 0x08009C02: complete 262-byte function. */
void func_08009AFC(u16 event)
{
    if (event != 0) {
        const ClearCallback *callbacks = g_callbacks_0836D4B8;
        EventQueue *queue = &data_02002194;

        callbacks[0](queue->entries, sizeof(queue->entries));
        queue->count = 1;
        queue->entries[0] = event;

        if (event == 0xAA || event == 0xAB)
            ((u8 *)queue)[-3] = 60;

        switch (event) {
        case 0xA2:
        case 0xA3:
        case 0xA4:
        case 0xA5:
            ((u8 *)queue)[-3] = 60;
            func_080C95C0(8, 1);
            func_080C9574(1, 0);
            break;
        case 0xA6:
            if (!func_080C9540(0x265) &&
                func_080C9540(0x371) &&
                func_080C9540(0x33A)) {
                func_080C9574(0x265, 1);
                callbacks[0](queue->entries, sizeof(queue->entries));
                queue->count = 1;
                queue->entries[0] = 0x96;
                func_080C9574(0x48C, 1);
                ((u8 *)queue)[-3] = 55;
                func_080C9574(1, 1);
                func_080C95C0(8, 0);
            } else {
                g_state_02000000[0x2191] = 60;
                func_080C95C0(8, 1);
                func_080C9574(1, 0);
            }
            break;
        default:
            func_080C9574(1, 1);
            func_080C95C0(8, 0);
            break;
        }
    }
}
