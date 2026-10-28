/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080100AC.c
 * Original SHA-256: 8d4a47aed978a6cb3a11d2dd084d779228f146661c7b22e5397bb69cdc4f6432
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 flags;
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_0800C64C(void *object);

/* Complete [0x080100AC, 0x080100E0): 52 bytes, 21 instructions. */
void func_080100AC(void *object, u8 enabled)
{
    RenderState *state = func_0800C614(object);

    if (enabled)
        state->flags |= 1;
    else
        state->flags &= 0xFFFE;
    func_0800C64C(object);
}
