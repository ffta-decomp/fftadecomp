/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018E94.c
 * Original SHA-256: c4b03be69ff79306ceb9a89928de8de32d4bceae3c1f694e4ad04aa972fcdb3d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern const u8 *func_080CB524(u32 identifier);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018E94..08018EB4: 32 bytes, 12 instructions. */
u32 func_08018E94(u8 *destination)
{
    func_08018C24(destination, func_080CB524(g_state_020020D0.identifier));
    return 0;
}
