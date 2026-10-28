/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DDA94.c
 * Original SHA-256: 093ed35d121a89962546792c0239a63040dc5871b21c4cb1d808037d0c34f452
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *object;
    u8 *result;
    u8 mode;
    s8 event;
    s8 repeat_count;
    u8 delay;
    u16 initial_delay;
} EventDefinition;

typedef struct {
    u16 state;
    u16 unknown_2;
    const EventDefinition *definition;
} EventCommand;

typedef struct {
    void *object;
    u8 *result;
    u8 mode;
    s8 event;
    s8 repeat_count;
    u8 delay;
    u8 seen;
    u8 unknown_D;
    u16 timer;
} EventState;

extern int func_08099C34(void *object);
extern u8 func_08097478(void *object, int event);
extern void func_0809A570(void *object, u32 set_flags, u32 clear_flags);

/* 0x080DDA94: 388 bytes. Wait for an object event and report completion. */
u32 func_080DDA94(void *task, EventCommand *command, EventState *state)
{
    switch (command->state) {
    case 0: {
        const EventDefinition *definition = command->definition;

        state->object = definition->object;
        state->result = definition->result;
        state->mode = definition->mode;
        state->event = definition->event;
        state->repeat_count = definition->repeat_count;
        state->delay = definition->delay;
        state->timer = definition->initial_delay;
        if (state->result)
            *state->result = 0;
        break;
    }
    case 1:
        if (state->mode == 2)
            func_0809A570(state->object, 0x100, 0);
        break;
    case 0x100:
        if (state->timer) {
            state->timer--;
            break;
        }
        if (state->mode == 0 || state->event == -1) {
            int event = func_08099C34(state->object);

            if (event == -1)
                break;
            if (state->event != -1 && state->event != event)
                break;
            if (state->repeat_count) {
                state->seen++;
                if (state->seen != state->repeat_count)
                    break;
            }
            if (state->mode == 0) {
                command->state = 2;
            } else if (state->mode == 1) {
                func_0809A570(state->object, 0, 0x100);
                if (state->delay)
                    command->state = 0x101;
                else
                    command->state = 2;
            } else {
                func_0809A570(state->object, 0, 0x100);
                command->state = 2;
            }
            if (state->result) {
                if (state->event != -1)
                    *state->result = state->event + 1;
                else
                    *state->result = event + 1;
            }
        } else {
            if (!func_08097478(state->object, state->event))
                break;
            if (state->repeat_count) {
                state->seen++;
                if (state->seen != state->repeat_count) {
                    func_0809A570(state->object, 0x100, 0);
                    break;
                }
            }
            if (state->mode == 1 && state->delay)
                command->state = 0x101;
            else
                command->state = 2;
            if (state->result)
                *state->result = state->event + 1;
        }
        break;
    case 0x101:
        if (--state->delay == 0) {
            func_0809A570(state->object, 0x100, 0);
            command->state = 2;
        }
        break;
    }
    return 0;
}
