/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D47C8.c
 * Original SHA-256: f7dcdccb7801fe64a13d8eb30f0a309c8bec0965f60586c5112ba4032b0fdedd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 value;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

void func_080D47C8(int index, u16 value)
{
    func_08005BFC(index)->value = value;
}
