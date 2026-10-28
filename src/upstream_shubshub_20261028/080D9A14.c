/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9A14.c
 * Original SHA-256: 657eda66362b1947cc659e8e6fe49113a90cf48e271cefe8d49f838ee3d3d23c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} ObjectState;

extern ObjectState *func_08005BFC(void *object);
extern void *func_0800C614(void *object);

void *func_080D9A14(void *object)
{
    return func_0800C614(func_08005BFC(object)->object);
}
