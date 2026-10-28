/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C5D60.c
 * Original SHA-256: 9c225a7bb08905712d61af75125bee43570a06caa7e1553a4c68daf1f8b01ec8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *context;
    u8 unknown_04[4];
    void *buffer;
    u8 unknown_0C[4];
    u16 width;
    u16 mode;
    u8 unknown_14;
    u8 index;
    u8 blocks;
    u8 unknown_17;
    u16 command;
    u16 count;
    u16 commands[34];
} CommandQueue080C5D60;

extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern u8 data_030028A0;
extern void *func_08022840(u32 size);

/* Complete target: [0x080C5D60, 0x080C5F92), 562 bytes. */
void func_080C5D60(CommandQueue080C5D60 *queue, void *context,
                   u16 width, u8 mode)
{
    g_callbacks_0836D4B8[0](queue, sizeof(CommandQueue080C5D60));
    queue->context = context;
    queue->mode = mode;
    queue->width = width + (width & 1);
    queue->index = 0;
    queue->blocks = queue->width / 64;
    queue->command = 0x15;
    queue->commands[queue->count++] = queue->command;
    queue->command = 0x0B;

    switch (queue->mode) {
    case 0:
        queue->commands[queue->count++] = queue->command;
        queue->command = 0x0A;
        queue->commands[queue->count++] = queue->command;
        queue->command = 0x0B;
        queue->commands[queue->count++] = queue->command;
        queue->command = 9;
        queue->commands[queue->count++] = queue->command;
        queue->command = 6;
        queue->commands[queue->count++] = queue->command;
        queue->command = 1;
        queue->commands[queue->count++] = queue->command;
        queue->command = 0;
        break;
    case 1:
        queue->commands[queue->count++] = queue->command;
        queue->command = 6;
        queue->commands[queue->count++] = queue->command;
        queue->command = 8;
        queue->commands[queue->count++] = queue->command;
        queue->command = 0x0B;
        queue->commands[queue->count++] = queue->command;
        queue->command = 1;
        queue->commands[queue->count++] = queue->command;
        queue->command = 0;
        break;
    default:
        if (data_030028A0 & 8) {
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x11;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x10;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0B;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0F;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0E;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0B;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0B;
        } else {
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x11;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x10;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0F;
            queue->commands[queue->count++] = queue->command;
            queue->command = 5;
            queue->commands[queue->count++] = queue->command;
            queue->command = 0x0B;
        }
        queue->commands[queue->count++] = queue->command;
        queue->command = 0x0D;
        queue->buffer = func_08022840(width);
        break;
    }
}
