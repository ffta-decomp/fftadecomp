/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813DAFC.c
 * Original SHA-256: 92f4827d4d0b2990b807a74af24dec286a16738a07a22ab781e6030f140a520a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct PaletteTransition PaletteTransition;

extern void func_08148704(PaletteTransition *transition, u8 enabled, u8 index);
extern void func_08148600(PaletteTransition *transition);

/* Complete [0x0813DAFC, 0x0813DB32): 54 bytes, 22 instructions. */
void func_0813DAFC(PaletteTransition *transition)
{
    func_08148704(transition, 1, 0);
    func_08148704(transition, 1, 1);
    func_08148704(transition, 1, 2);
    func_08148704(transition, 1, 3);
    func_08148600(transition);
}
