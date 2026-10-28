/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08055EC0.c
 * Original SHA-256: 1f1763607e936fbfd2361aa1d6fd56bdd7d54765543bdc28f4203d955652885d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA8];
    u16 flags;
    u8 unknown_AA[0x5E];
} MenuUnit;

typedef struct {
    u8 unknown_00[0x2D3A];
    u8 unitIds[0x1B];
    u8 selection;
} MenuSelection;

extern MenuUnit g_state_02000000[];
extern MenuSelection *data_0200F428;
extern void func_08141540(u32 sound);

void func_08055EC0(u8 *state)
{
    func_08141540(0x64);
    if (!(g_state_02000000[data_0200F428->unitIds[data_0200F428->selection]].flags & 0x10))
        *state = 0x64;
    else
        *state = 0x78;
}
