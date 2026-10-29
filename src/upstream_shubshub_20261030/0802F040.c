/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0802F040.c
 * Original SHA-256: b45ff45dd90335263f82551325dd1d2bd03e2c0876f225d627aca79459034a8d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1F3C];
    u8 selections[0][2];
    u8 unknown_1F3C[0x1CF6];
    u8 capacity;
    u8 count;
    u16 entries[256];
} SelectionState;

typedef struct {
    u8 unknown_00[7];
    u8 step;
    u8 height;
    u8 mask;
    u8 unknown_0A[2];
    s16 selected;
} TextPanel;

extern SelectionState g_state_02000000;
extern TextPanel *data_0200F444;
extern void func_0802D7A0(void);
extern void func_08038678(u16 selected);
extern u8 func_0802D764(void);
extern void func_080CC2B4(void);
extern void func_0802E070(void);

/* Complete [0x0802F040, 0x0802F100): 192 bytes, 73 instructions. */
void func_0802F040(void)
{
    u8 value = g_state_02000000.selections[data_0200F444->selected][0];
    int i;

    if (value > 0x55) {
        for (i = 0; i < data_0200F444->step; i++) {
            if (g_state_02000000.entries[i] != 0 &&
                ((data_0200F444->mask >> i) & 1)) {
                g_state_02000000.entries[i] = 0;
            }
        }
        func_0802D7A0();
    } else {
        for (i = 0; i < g_state_02000000.capacity; i++) {
            if (g_state_02000000.entries[i] == 0) {
                g_state_02000000.entries[i] = value;
                break;
            }
        }
    }
    func_08038678(data_0200F444->selected);
    g_state_02000000.count = func_0802D764();
    func_080CC2B4();
    func_0802E070();
}
