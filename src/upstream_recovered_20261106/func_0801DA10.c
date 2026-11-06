/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0801DA10.c
 * Original SHA-256: 28dbfc94182044e3e47219a758779aee25a05a32780ef2db2c095a0cd2b19720
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct LineState {
    s32 x, y, endX, endY, stepX, stepY;
    s32 deltaX, deltaY, accumulator, error, remaining;
} LineState;

typedef struct TransferState {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11;
    u16 selector;
    u8 unknown_14[2];
    u8 pending;
    u8 unknown_17;
    const u16 *source;
} TransferState;

typedef struct WindowState {
    u8 active;
    u8 unknown_01;
    u16 selector;
    u16 width;
    u8 unknown_06[6];
    s16 left;
    s16 right;
    const u16 *first;
    const u16 *second;
} WindowState;

typedef struct PositionState {
    u8 unknown_00[0x26];
    u16 position;
} PositionState;

typedef union Controller {
    TransferState transfer;
    struct {
        u8 unknown_00[0x10];
        WindowState window;
    } local;
} Controller;

extern Controller data_02007F10;
extern PositionState g_state_02007F40;
extern u16 data_02008390[];
extern u16 data_03003860;
extern void func_080075CC(LineState *, s32, s32, s32, s32);
extern void func_080076A0(LineState *);
extern void func_0814186C(const void *, void *, u32);

void func_0801DA10(void)
{
    WindowState *window = &data_02007F10.local.window;
    LineState line;
    const u16 *source;
    u16 position;
    u16 offset;
    s16 x;

    if (window->selector == 0xFF)
        return;
    if (!window->active)
        return;
    position = g_state_02007F40.position;
    if (window->width > 160) {
        x = position;
        if (x < window->left)
            source = window->first;
        else if (x >= window->right)
            source = window->second;
        else {
            offset = window->width - 160;
            if (x < ((window->right - window->left) >> 1)) {
                func_080075CC(&line, window->left, 0,
                             window->right, offset);
                while (line.x < x)
                    func_080076A0(&line);
                offset -= line.remaining;
            } else {
                func_080075CC(&line, window->right, offset,
                             window->left, 0);
                while (line.x > x)
                    func_080076A0(&line);
                offset = line.remaining;
            }
            source = window->first + offset;
        }

        if (data_02007F10.transfer.selector == 0xFF)
            return;
        if (data_02007F10.transfer.enabled) {
            data_02007F10.transfer.pending = 1;
            data_02007F10.transfer.source = source;
            data_03003860 = source[0];
        } else {
            func_0814186C(source, data_02008390, 0xA1);
            data_02008390[160] = data_02008390[0];
        }
    } else {
        source = window->first;
        if (data_02007F10.transfer.selector == 0xFF)
            return;
        if (data_02007F10.transfer.enabled) {
            data_02007F10.transfer.pending = 1;
            data_02007F10.transfer.source = source;
            data_03003860 = source[0];
        } else {
            func_0814186C(source, data_02008390, 0xA1);
            data_02008390[160] = data_02008390[0];
        }
    }
}
