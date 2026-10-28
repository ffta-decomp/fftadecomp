/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08088CDC.c
 * Original SHA-256: 5446d0a497b64667632a8e8ef3b0cb3e5a7a8ae28fd44addf3e4dec34bc81794
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x08088CDC - 274 bytes: generate a sampled, vertically scaled ring. */
#include "ffta.h"

typedef struct {
    s32 x;
    s32 y;
} RingPoint;

extern s32 func_08007A4C(u8 angle);
extern s16 func_08007A60(u8 angle);

u16 func_08088CDC(s32 segments, s32 center_x, s32 center_y,
                  RingPoint *points, s32 radius)
{
    u16 count = 0;
    u16 alternate = 0;
    s32 skipped = 0;
    RingPoint point;
    s32 samples = segments * 8 + 8;
    s32 circumference = segments * 8;
    s32 half_circumference = circumference >> 1;
    s32 i;

    for (i = 0; i < samples; i++) {
        s32 angle = (i << 8) / samples;

        if (skipped <= 7 && i > (samples >> 1) - 8)
            alternate++;
        else
            alternate = 0;

        if (skipped >= 8 || !(alternate & 1)) {
            s32 index;

            point.x = center_x + (s16)func_08007A4C(angle) * radius / 256;
            point.y = center_y - (radius * func_08007A60(angle) / 256) * 0.4;
            index = (count + half_circumference) % circumference;
            points[index] = point;
            count++;
        } else {
            skipped++;
        }
    }
    return count;
}
