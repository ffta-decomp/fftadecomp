/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080314C8.c
 * Original SHA-256: c370b2d38d2e524ba0b9ce4c6ca340c69d7255a1a78c5336bba886d62360840a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2fc2];
    u8 selection : 2;
    u8 unknown_2fc2 : 6;
} Global080314C8;

typedef struct {
    u8 unknown_00[0xa0];
    u8 first[0x200];
    u8 second[0x200];
} State080314C8;

extern Global080314C8 g_state_02000000;
extern State080314C8 *g_state_03002810;
extern const void *data_08391960[];
extern u8 data_03003860[];
extern void func_0814186C(const void *, void *, u32);

/* Complete [0x080314C8, 0x0803155C): 148 bytes, 58 instructions. */
void func_080314C8(u32 update)
{
    func_0814186C(data_08391960[g_state_02000000.selection * 2],
                  g_state_03002810->first, 0x100);
    func_0814186C(data_08391960[g_state_02000000.selection * 2 + 1],
                  g_state_03002810->second, 0x100);
    if (update) {
        func_0814186C(g_state_03002810->first, data_03003860, 0x04000080);
        func_0814186C(g_state_03002810->second, data_03003860 + 0x200,
                      0x04000080);
    }
}
