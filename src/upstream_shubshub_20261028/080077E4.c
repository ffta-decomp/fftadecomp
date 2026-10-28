/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080077E4.c
 * Original SHA-256: 704b8933f7880945931923ce0e70985b0d06ddb039e4f08613759403bf49abcb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Motion080077E4 {
    s16 position;
    s16 offset;
    u16 unknown_04[2];
    s16 position_step;
    s16 offset_step;
    s16 remainder_step;
    s16 threshold;
    s16 remainder;
    s16 rounding_threshold;
    s16 remaining;
};

/* Target: [0x080077E4, 0x0800787E), 154 bytes, 77 instructions. */
void func_080077E4(struct Motion080077E4 *motion, u16 amount)
{
    if (motion->remaining > 0) {
        if (amount > motion->remaining)
            amount = motion->remaining;
        motion->remaining -= amount;
        motion->offset += motion->offset_step * amount;
        motion->remainder += motion->remainder_step * amount;
        while (motion->remainder >= motion->threshold) {
            motion->position += motion->position_step;
            motion->remainder -= motion->threshold;
        }
        if (motion->rounding_threshold > 0 &&
            motion->remainder >= motion->rounding_threshold) {
            motion->remainder -= motion->threshold;
            motion->position += motion->position_step;
        }
    }
}
