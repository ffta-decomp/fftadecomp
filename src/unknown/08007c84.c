typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

struct PathInterpolationState {
    const double *first_points;
    const double *second_points;
    s32 point_count;
    u8 phase;
    u8 unused_0d[3];
    s32 current_index;
    s32 first_index;
    s32 end_index;
    double coefficients[32];
};
typedef char StateSize[sizeof(struct PathInterpolationState) == 284 ? 1 : -1];

/* Existing numeric runtime interface; argument order is observable in the native ABI. */
extern double __muldf3(double scale, double ordinal) __attribute__((const));

u32 AdvancePathInterpolation(struct PathInterpolationState *state,
    double *first_output, double *second_output)
{
    s32 sample_index;
    double fraction, square, cube;
    const double *first_current, *first_previous;
    const double *second_current, *second_previous;
    s32 first_index;
    const double *first_points;
    s32 end_index;
    const double *second_points;
    s32 current_index;
    double *second_sample, *first_sample;
    s32 point_count;
    struct PathInterpolationState *coefficient;
    double first_value, second_value;
    const double *lower_coefficients, *upper_coefficients;
    u32 point_byte_offset, output_byte_offset;

    switch (state->phase) {
    case 0:
        state->current_index = 0;
        point_count = state->point_count;
        do {
            {
                register double produced asm("r0") = __muldf3(0.125, (double)state->current_index);
                /* Capture only the actual R0/R1 numeric return; the snapshot is ordinary C. */
                asm("" : "+r" (produced));
                fraction = produced;
            }
            /* State-relative address view: only the four coefficient lanes are accessed. */
            coefficient = (struct PathInterpolationState *)((u8 *)state
                + state->current_index * sizeof(double));
            {
                register double produced asm("r0") = fraction * fraction;
                /* Capture only the actual R0/R1 numeric return; the snapshot is ordinary C. */
                asm("" : "+r" (produced));
                square = produced;
            }
            {
                register double produced asm("r0") = square * fraction;
                /* Capture only the actual R0/R1 numeric return; the snapshot is ordinary C. */
                asm("" : "+r" (produced));
                cube = produced;
            }
            coefficient->coefficients[0] = cube / 6.0;
            coefficient->coefficients[8] =
                (((-cube + square) + fraction) * 3.0 + 1.0) / 6.0;
            coefficient->coefficients[16] =
                ((cube * 3.0 - square * 6.0) + 4.0) / 6.0;
            coefficient->coefficients[24] =
                (((square - fraction) * 3.0 - cube) + 1.0) / 6.0;
            ++state->current_index;
        } while (state->current_index <= 7);
        state->first_index = 2;
        state->end_index = point_count + 1;
        state->current_index = 2;
        state->phase = 1;
        break;
    case 1:
        current_index = state->current_index;
        end_index = state->end_index;
        if (current_index >= end_index) {
            state->phase = 2;
            return 0;
        }
        sample_index = 0;
        first_points = state->first_points;
        second_points = state->second_points;
        first_index = state->first_index;
        point_byte_offset = (u32)current_index * sizeof(double);
        first_current = (const double *)(point_byte_offset + (u32)first_points);
        first_previous = first_current - 1;
        second_current = (const double *)(point_byte_offset + (u32)second_points);
        second_previous = second_current - 1;
        output_byte_offset = ((u32)current_index - (u32)first_index)
            * 8 * sizeof(double);
        second_sample = (double *)(output_byte_offset + (u32)second_output);
        first_sample = (double *)(output_byte_offset + (u32)first_output);
        upper_coefficients = state->coefficients + 16;
        lower_coefficients = state->coefficients;
        /* Preserve the actual initialized embedded bases consumed across runtime calls. */
        asm("" : "+r" (upper_coefficients), "+r" (lower_coefficients));
        do {
            first_value = first_current[2] * lower_coefficients[0];
            first_value += first_current[1] * lower_coefficients[8];
            first_value += first_current[0] * upper_coefficients[0];
            first_value += first_previous[0] * upper_coefficients[8];
            second_value = second_current[2] * lower_coefficients[0];
            second_value += second_current[1] * lower_coefficients[8];
            second_value += second_current[0] * upper_coefficients[0];
            second_value += second_previous[0] * upper_coefficients[8];
            *first_sample++ = first_value;
            *second_sample++ = second_value;
            ++upper_coefficients;
            ++lower_coefficients;
            ++sample_index;
            /* The initialized ascending sample number is the real loop-test input. */
            asm("" : "+r" (sample_index));
        } while (sample_index <= 7);
        /* The endpoint address is formed in the post-sample phase. */
        {
            s32 endpoint_index = end_index;
            asm volatile("" : "+r" (endpoint_index));
            first_output[(endpoint_index - first_index) * 8] = first_points[endpoint_index];
            second_output[(endpoint_index - first_index) * 8] = second_points[endpoint_index];
        }
        /* Preserve the actual current index until its post-output increment. */
        {
            s32 next_index = current_index;
            asm volatile("" : "+r" (next_index));
            current_index = next_index + 1;
        }
        state->current_index = current_index;
        if (current_index >= end_index) {
            state->phase = 2;
            return 0;
        }
        break;
    }
    return 1;
}

asm(".global __adddf3\n.thumb_set __adddf3,0x08143081\n"
    ".global __subdf3\n.thumb_set __subdf3,0x081430b5\n"
    ".global __muldf3\n.thumb_set __muldf3,0x081430f1\n"
    ".global __divdf3\n.thumb_set __divdf3,0x0814339d\n"
    ".global __floatsidf\n.thumb_set __floatsidf,0x0814383d\n"
    ".global __negdf2\n.thumb_set __negdf2,0x08143931\n");
