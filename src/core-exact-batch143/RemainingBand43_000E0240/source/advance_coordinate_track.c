typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed long long s64;

struct CoordinateTrack {
    u16 start_x, start_y, start_z;
    u16 end_x, end_y, end_z;
    u16 curve_height, count;
    u16 *x_values, *y_values, *z_values;
    s64 control_y[3];
    s64 progress, halfway, final_step;
};
struct TrackParameters {
    u16 start_x, start_y, start_z, end_x, end_y, end_z;
    u16 curve_height, count;
    u16 *x_values, *y_values, *z_values;
};
struct TrackEvent {
    u16 state, unknown02;
    const struct TrackParameters *parameters;
    u32 unknown08[5];
};
struct DefinitionRamp {
    u16 value;
    s16 remaining, error;
    u16 step, period, magnitude;
};
typedef char TrackMustBe76[sizeof(struct CoordinateTrack)==76?1:-1];
typedef char ControlOffset28[(u32)&((struct CoordinateTrack*)0)->control_y==28?1:-1];
typedef char ProgressOffset52[(u32)&((struct CoordinateTrack*)0)->progress==52?1:-1];
typedef char RampMustBe12[sizeof(struct DefinitionRamp)==12?1:-1];

extern void GenerateDefinitionCurve(u16 dimensions, s64 *progress,
        s64 *control, u16 *output, u16 count);
/* These sites pass sign-extended working values; the real callee uses LOW16. */
extern void InitializeDefinitionRamp(struct DefinitionRamp *, int, int, int);
extern void AdvanceDefinitionRamp(struct DefinitionRamp *);
extern u32 IsDefinitionRampComplete(const struct DefinitionRamp *);

u32 AdvanceCoordinateTrack(void *task, struct TrackEvent *event,
                           struct CoordinateTrack *track)
{
    struct DefinitionRamp x_ramp, z_ramp;
    switch (event->state) {
    case 0: {
        const struct TrackParameters *parameters = event->parameters;
        track->start_x = parameters->start_x;
        track->start_y = parameters->start_y;
        track->start_z = parameters->start_z;
        track->end_x = parameters->end_x;
        track->end_y = parameters->end_y;
        track->end_z = parameters->end_z;
        track->curve_height = parameters->curve_height;
        track->count = parameters->count;
        track->x_values = parameters->x_values;
        track->y_values = parameters->y_values;
        track->z_values = parameters->z_values;
        break;
    }
    /* The real task teardown invokes state1, which has no cleanup here. */
    case 1:
        break;
    case 256: {
        u16 midpoint = (s16)(track->start_y + track->end_y) >> 1;
        midpoint += track->curve_height;
        /* Signed wrapping halfwords become the observed 64-bit Q16 values. */
        track->control_y[1] = (s64)(s16)midpoint << 16;
        track->control_y[0] = (s64)(s16)track->start_y << 16;
        track->control_y[2] = (s64)(s16)track->end_y << 16;
        track->progress = 0;
        track->halfway = (s64)(track->count >> 1) << 16;
        track->final_step = (s64)(track->count - 1) << 16;
        ++event->state;
        break;
    }
    case 257:
        GenerateDefinitionCurve(3, &track->progress, track->control_y,
                                track->y_values, track->count);
        if (track->x_values == 0) {
            if (track->z_values != 0)
                event->state = 259;
            else
                event->state = 2;
        } else
            ++event->state;
        break;
    case 258: {
        u16 index;
        InitializeDefinitionRamp(&x_ramp, (s16)track->start_x,
                                (s16)track->end_x, (s16)(track->count - 1));
        track->x_values[0] = track->start_x;
        index = 1;
        do {
            AdvanceDefinitionRamp(&x_ramp);
            track->x_values[index] = x_ramp.value;
            ++index;
        } while ((u8)IsDefinitionRampComplete(&x_ramp) == 0);
        if (track->z_values != 0)
            ++event->state;
        else
            event->state = 2;
        break;
    }
    case 259: {
        u16 index;
        InitializeDefinitionRamp(&z_ramp, (s16)track->start_z,
                                (s16)track->end_z, (s16)(track->count - 1));
        track->z_values[0] = track->start_z;
        index = 1;
        do {
            AdvanceDefinitionRamp(&z_ramp);
            track->z_values[index] = z_ramp.value;
            ++index;
        } while ((u8)IsDefinitionRampComplete(&z_ramp) == 0);
        event->state = 2;
        break;
    }
    }
    return 0;
}

asm(".global GenerateDefinitionCurve\n.thumb_set GenerateDefinitionCurve,0x080E06A5\n"
    ".global InitializeDefinitionRamp\n.thumb_set InitializeDefinitionRamp,0x080E0609\n"
    ".global AdvanceDefinitionRamp\n.thumb_set AdvanceDefinitionRamp,0x080E064D\n"
    ".global IsDefinitionRampComplete\n.thumb_set IsDefinitionRampComplete,0x080E0691\n");
