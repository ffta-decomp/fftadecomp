/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CA150.c
 * Original SHA-256: c66734333d28b9f0c9d853447e57fb641e479ca3cb72b66fb1058b060e2368de
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedKey;

extern const u32 g_table_085680DC[];
extern const u32 g_table_085516D0[];

u32 func_080CA150(const PackedKey *key)
{
    u32 i;

    for (i = 0; i < 725; i++) {
        if (g_table_085680DC[i] ==
            key->value)
            return i;
    }
    for (i = 0; i < 107; i++) {
        if (g_table_085516D0[i] ==
            key->value)
            return i | 0x8000;
    }
    return 0;
}
