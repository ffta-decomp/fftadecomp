/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081485E8.c
 * Original SHA-256: 2d253d6eb77f25ec8ef868638da91d1f76d78dbf54e7b6aad87dd98913f1c773
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 state;
    u16 unknown_02;
    u16 value;
} EffectValue;

u16 func_081485E8(const EffectValue *effect)
{
    if (effect->state == 0)
        return 0x8000;
    return effect->value;
}
