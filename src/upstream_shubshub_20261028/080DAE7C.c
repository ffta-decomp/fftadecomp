/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DAE7C.c
 * Original SHA-256: f72109e130a06bd62d45820c1fc43908848df9fd813c22d7916cf6914ad75192
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    void *resource;
    u8 type;
    u8 palette;
    u16 value;
} TransitionDefinition;

typedef struct {
    s16 opening_speed;
    s16 delay;
    s16 closing_speed;
    u16 initial_delay;
} TransitionOptions;

typedef struct {
    u16 state;
    u16 unknown_2;
    const TransitionDefinition *definition;
    const TransitionOptions *options;
} TransitionTask;

typedef struct {
    void *resource;
    u8 type;
    u8 opening_speed;
    u8 delay;
    u8 closing_speed;
    u16 timer;
    u16 value;
    u8 saved_palette;
    u8 palette;
    u8 unknown_E[2];
    void *effect;
} TransitionState;

typedef struct {
    u8 mode;
    u8 parameter_index;
    u8 unknown_2[2];
} TransitionStyle;

typedef struct {
    u16 value;
    u8 first;
    u8 second;
} EffectParameters;

extern const TransitionStyle data_08395574[];
extern const EffectParameters data_0839554C[];
extern const u16 data_03003A62[][16];

extern u8 func_080DBC58(void *resource, u8 palette);
extern void func_080DBC18(void *resource, u8 palette);
extern void *func_08147D94(u16 first_color, u16 mask, u8 speed,
                         u16 value, u8 first, u8 second);
extern void *func_08147B28(u16 first_color, u16 mask, u8 speed);
extern void *func_08147D2C(u16 first_color, u16 mask, u8 speed,
                         const u16 *palette);
extern u32 func_081485D4(void *effect);
extern void func_08148498(void *effect);

/* 0x080DAE7C: 398 bytes. Advance a resource's palette transition. */
u32 func_080DAE7C(void *task, TransitionTask *control, TransitionState *state)
{
    switch (control->state) {
    case 0: {
        const TransitionDefinition *definition = control->definition;
        const TransitionOptions *options;

        state->resource = definition->resource;
        state->type = definition->type;
        state->palette = definition->palette;
        state->value = definition->value;
        options = control->options;
        state->opening_speed = 6;
        state->delay = 4;
        state->closing_speed = 6;
        if (options) {
            if (options->opening_speed != -1)
                state->opening_speed = options->opening_speed;
            if (options->delay != -1)
                state->delay = options->delay;
            if (options->closing_speed != -1)
                state->closing_speed = options->closing_speed;
            state->timer = options->initial_delay;
        }
        break;
    }
    case 1:
        break;
    case 0x100: {
        const TransitionStyle *style;

        if (state->timer && --state->timer)
            break;
        state->saved_palette = func_080DBC58(state->resource, state->palette);
        style = &data_08395574[state->type];
        if (style->mode == 0) {
            const EffectParameters *parameters = &data_0839554C[style->parameter_index];

            state->effect = func_08147D94((u16)(0x101 + (state->palette << 4)), 15,
                state->opening_speed, parameters->value, parameters->first,
                parameters->second);
        } else if (style->mode == 1) {
            state->effect = func_08147B28((u16)(0x101 + (state->palette << 4)), 15,
                                        state->opening_speed);
        }
        control->state++;
        break;
    }
    case 0x101:
        if (state->effect) {
            if (!func_081485D4(state->effect))
                break;
            func_08148498(state->effect);
            state->effect = 0;
            state->timer = state->delay;
        }
        control->state++;
        break;
    case 0x102:
        if (state->timer && --state->timer)
            break;
        state->effect = func_08147D2C((u16)(0x101 + (state->palette << 4)), 15,
            state->closing_speed, data_03003A62[state->saved_palette]);
        control->state++;
        break;
    case 0x103:
        if (state->effect) {
            if (!func_081485D4(state->effect))
                break;
            func_08148498(state->effect);
            state->effect = 0;
        }
        func_080DBC18(state->resource, state->saved_palette);
        control->state = 2;
        break;
    }
    return 0;
}
