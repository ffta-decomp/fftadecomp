/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08145358.c
 * Original SHA-256: 17bdf711ac97ea8ad1842baae1f794e657a22bdbc55cfd94726416465d06774b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct AudioState AudioState;

extern void func_0814511C(AudioState *state, u16 interval);

void func_08145358(AudioState *state, u16 interval)
{
    func_0814511C(state, interval);
}
