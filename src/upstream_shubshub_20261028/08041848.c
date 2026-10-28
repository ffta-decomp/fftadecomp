/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08041848.c
 * Original SHA-256: f064926e3a6fd3b7488c338b5aa98794fc155e034f385e18fa1d3a17ea04bbc7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TextEntry08041848 {
    u8 unknown_00[8];
    u8 *text;
    u8 unknown_0C[8];
};

struct TextResources08041848 {
    u8 unknown_00[0x18];
    struct TextEntry08041848 *entries;
};

struct MenuState08041848 {
    u8 unknown_000[0xC4C];
    u8 text_state[1];
};

extern u8 data_02003CB0[];
extern struct MenuState08041848 *g_state_03002810;
extern void func_080CB9B0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);

/* Complete target: [0x08041848, 0x080418B4), 108 bytes. */
void func_08041848(u32 graphic, u16 index, u8 *tiles,
                  struct TextResources08041848 *resources)
{
    u8 *source = data_02003CB0;

    func_080CB9B0(source, (u8)graphic);
    func_0814186C(source, tiles, 0x40);
    source = resources->entries[index].text;
    func_08015110(g_state_03002810->text_state, tiles + 0x80, source, 0, 1);
}
