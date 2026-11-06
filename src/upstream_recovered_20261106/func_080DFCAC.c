/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080DFCAC.c
 * Original SHA-256: bbc0b3a0e252b2f87248ab7aaa3da32fdb12bef2ca7839367f4663786b9c4650
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolator080DFCAC;

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    u16 direction;
    s16 duration;
} FadeDescriptor080DFCAC;

typedef struct {
    float value;
    u8 direction;
    u8 unknown_05[3];
    Interpolator080DFCAC interpolation;
} FadePayload080DFCAC;

extern const float g_table_08149B88[];
extern void func_080E0608(Interpolator080DFCAC *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(Interpolator080DFCAC *state);
extern u8 func_080E0690(Interpolator080DFCAC *state);
extern void func_08141780(float value);

/* 0x080DFCAC - 188 bytes, including literal pools.
 * Target: 70b50e1c151c3188012950d0012902dc002905d04be080204000814224d046e0b08a
 *         28710006002808d1281c08301621735e2021002200f091fc07e0281c08301622b35e
 *         0021202200f088fc2879002804d1014828602ae00000003f0148286025e000000000
 *         803f2c1c0834201c00f097fc09490822a85e8000401800682860201c00f0affc0006
 *         00280dd02879002806d1024805e00000889b14080000803f05482860022030802868
 *         61f013fd002070bc02bc084700000000003f
 */
u32 func_080DFCAC(void *task, FadeDescriptor080DFCAC *event,
                    FadePayload080DFCAC *state)
{

    switch (event->phase) {
    case 0:
        state->direction = event->direction;
        if (state->direction == 0)
            func_080E0608(&state->interpolation, 32, 0, event->duration);
        else
            func_080E0608(&state->interpolation, 0, 32, event->duration);
        if (state->direction == 0)
            state->value = 0.5f;
        else
            state->value = 1.0f;
        break;
    case 1:
        break;
    case 0x100:
        func_080E064C(&state->interpolation);
        state->value = g_table_08149B88[state->interpolation.current];
        if (func_080E0690(&state->interpolation)) {
            if (state->direction == 0)
                state->value = 1.0f;
            else
                state->value = 0.5f;
            event->phase = 2;
        }
        func_08141780(state->value);
        break;
    }
    return 0;
}
