/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0804D6B0.c
 * Original SHA-256: b70df2b0dc1fe397fa0584c32feb76bc5c2292184cf206745be5b44652e5319e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00;
    u8 enabled;
    u8 mode;
    u8 unknown_03[5];
    u16 current;
    u16 count;
    u16 commands[8];
} CommandState0804D6B0;

extern CommandState0804D6B0 *data_0201F544;
extern void func_0804D5AC(u8 enabled);

/* Complete [0x0804D6B0, 0x0804D7E8): 312 bytes. */
void func_0804D6B0(s16 mode)
{
    switch (mode) {
    case -1:
        func_0804D5AC(7);
        data_0201F544->current = 26;
        data_0201F544->commands[data_0201F544->count++] = 26;
        data_0201F544->current = 24;
        break;
    case 1:
        func_0804D5AC(2);
        data_0201F544->mode = 3;
        data_0201F544->current = 5;
        data_0201F544->commands[data_0201F544->count++] = 5;
        data_0201F544->current = 23;
        data_0201F544->commands[data_0201F544->count++] = 23;
        data_0201F544->current = 24;
        break;
    case 2:
        func_0804D5AC(3);
        data_0201F544->mode = 8;
        data_0201F544->current = 7;
        data_0201F544->commands[data_0201F544->count++] = 7;
        data_0201F544->current = 23;
        data_0201F544->commands[data_0201F544->count++] = 23;
        data_0201F544->current = 24;
        break;
    case 3:
        func_0804D5AC(7);
        data_0201F544->current = 9;
        data_0201F544->commands[data_0201F544->count++] = 9;
        data_0201F544->current = 24;
        break;
    case 4:
        func_0804D5AC(2);
        data_0201F544->mode = 4;
        data_0201F544->current = 11;
        data_0201F544->commands[data_0201F544->count++] = 11;
        data_0201F544->current = 23;
        data_0201F544->commands[data_0201F544->count++] = 23;
        data_0201F544->current = 24;
        break;
    case 5:
        func_0804D5AC(2);
        data_0201F544->mode = 5;
        data_0201F544->current = 16;
        data_0201F544->commands[data_0201F544->count++] = 16;
        data_0201F544->current = 23;
        data_0201F544->commands[data_0201F544->count++] = 23;
        data_0201F544->current = 24;
        break;
    case 6:
        func_0804D5AC(2);
        data_0201F544->mode = 6;
        data_0201F544->current = 20;
        data_0201F544->commands[data_0201F544->count++] = 20;
        data_0201F544->current = 23;
        data_0201F544->commands[data_0201F544->count++] = 23;
        data_0201F544->current = 24;
        break;
    }
}
