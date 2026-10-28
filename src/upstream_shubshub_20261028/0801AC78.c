/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801AC78.c
 * Original SHA-256: 1f83ca7c33e71597c5b2250179c18371617d92fa515e528ef1148f5fa8548fb3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State0801AC78 {
    u8 unknown_00[0x14];
    void *first;
    void *second;
    u8 unknown_1C[0x10];
    u16 flags;
};

extern u16 data_03000E10;
extern u8 data_02009198;
extern u8 data_020091A0[];
extern struct State0801AC78 g_state_02007F40;
extern void func_08020BA0(u8 enabled);
extern u8 func_0801B888(void);
extern void func_0801B7F8(struct State0801AC78 *state, void *first, void *second,
                          void *buffer, void *secondary_buffer, u32 enabled);
extern u8 func_0801D928(void);
extern void func_0801D818(void);
extern void func_08019C74(void);
extern void func_08019B48(void);
extern void func_0801DD68(void);

/* Complete [0x0801AC78, 0x0801AD1C): 164 bytes, 61 instructions. */
void func_0801AC78(void)
{
    if (data_03000E10 != 0 || data_02009198 != 0)
        return;
    data_02009198 = 1;
    func_08020BA0(1);
    if (func_0801B888()) {
        struct State0801AC78 *state = &g_state_02007F40;

        func_0801B7F8(state, state->first, state->second,
                      data_020091A0, data_020091A0 + 0x2000, 1);
        state->flags |= 0x200;
    } else {
        func_08020BA0(0);
    }
    if (func_0801D928()) {
        func_0801D818();
        func_08019C74();
    }
    if (g_state_02007F40.flags & 0x200)
        func_08019B48();
    func_0801DD68();
    data_02009198 = 0;
}
