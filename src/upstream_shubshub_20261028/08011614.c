/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011614.c
 * Original SHA-256: 56da4d007515a727f36319e51a76ac8e727e964873429a1cbc600cdcc260faad
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    void *allocation;
} ReleaseState;

extern void *data_02009168;
extern ReleaseState data_02009170;
extern void func_08007170(void *allocator, void *allocation);

/* 08011614..08011634: 32 bytes. */
void func_08011614(void)
{
    void *allocator = data_02009168;
    ReleaseState *state = &data_02009170;

    func_08007170(allocator, state->allocation);
    state->allocation = 0;
}
