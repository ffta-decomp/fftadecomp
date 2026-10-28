/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812F17C.c
 * Original SHA-256: a2fd7a5f8e1ae1c48ac41e7d8f7de5decfb26fb42d45d6538d605bca45103c67
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 func_080CD8CC(void *unit);

u8 func_0812F17C(void *unit)
{
    if (func_080CD8CC(unit) != 0)
        return 1;
    return 0;
}
