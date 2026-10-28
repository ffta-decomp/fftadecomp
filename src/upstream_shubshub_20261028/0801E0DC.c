/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801E0DC.c
 * Original SHA-256: 0c98990311a641c10c13b06048e465b78f3b7335ed7ddf4ca7999abd3536fbbf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 first_layer;
    u8 second_layer;
    u8 unknown_02[10];
    u16 origin_x;
    u16 origin_y;
    u8 unknown_10[0x14];
    u16 target_x;
    u16 target_y;
    u16 shift_x;
    u16 shift_y;
} ScrollState;

extern ScrollState g_state_02007F40;
extern void func_08003508(s16 coordinate, u8 layer);
extern void func_08003558(s16 coordinate, u8 layer);
extern void func_0801B878(void);

/* 0801E0DC..0801E144: 104 bytes, 45 instructions. */
void func_0801E0DC(u16 x, u16 y)
{
    g_state_02007F40.target_x = x;
    g_state_02007F40.target_y = y;
    g_state_02007F40.shift_x = (x - g_state_02007F40.origin_x) & ~7;
    g_state_02007F40.shift_y = (y - g_state_02007F40.origin_y) & ~7;
    x -= g_state_02007F40.shift_x;
    y -= g_state_02007F40.shift_y;

    func_08003508(x, g_state_02007F40.first_layer);
    func_08003558(y, g_state_02007F40.first_layer);
    func_08003508(x, g_state_02007F40.second_layer);
    func_08003558(y, g_state_02007F40.second_layer);
    func_0801B878();
}
