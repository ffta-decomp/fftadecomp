/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08012910.c
 * Original SHA-256: fa5ada7507797651caf3a098ac801046fd3323e8e7cfbe6f2f2abb96dd5e637c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 pending_offset;
    u16 scale;
    u16 limit;
    u8 unknown_1A[0x2EE];
    const u8 *active;
    u8 fallback[1];
} Context08012910;

extern Context08012910 *data_0200918C;

u8 func_08012910(void)
{
    Context08012910 *context = data_0200918C;

    if (context->pending_offset == 0)
        return 0;

    context->limit += 0x100;
    context->active = context->fallback + context->pending_offset;
    context->pending_offset = 0;
    return 1;
}
