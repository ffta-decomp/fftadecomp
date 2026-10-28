/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EB514.c
 * Original SHA-256: 5ff40478583bc7dc5a14093afcc1d7f367275d09453da4b1abf2a7ea71c9aee0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command080EB514 {
    u16 state;
};

struct Tween080EB514 {
    u8 unknown_00[0x2C];
};

struct Effect080EB514 {
    u16 state;
    u16 unknown_02;
    struct Tween080EB514 scale;
    struct Tween080EB514 x;
    struct Tween080EB514 y;
    u16 unknown_88;
    u16 delay;
};

struct Runtime080EB514 {
    u16 time;
    u16 state;
    u32 parameters[2];
    void *operation;
    void *overlay;
    struct Tween080EB514 scale;
    u32 unknown_40;
    void *objects[8];
    struct Effect080EB514 effects[8];
    void *script;
    void *event;
};

struct Entry080EB514 {
    u8 type;
    u8 id;
    u16 time;
    s16 x;
    s16 y;
    s16 end_x;
    s16 end_y;
    u16 duration;
    u16 delay;
};

extern const u8 data_08398FCC[];
extern const struct Entry080EB514 data_08398F24[];
extern const u8 data_084F7B24[];
extern const u8 data_08398EDC[];
extern const u8 data_08398FE4[];

extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern u16 func_080D5FA4(void **objects, u16 count);
extern void *func_080D5CC0(const void *data, u8 id, s16 x, s16 y,
                          u16 resource, u16 priority, u32 first, u32 second);
extern void func_080110F8(void *object, u8 enabled);
extern void func_080112CC(void *object, s16 x, s16 y, u16 value);
extern void func_080112E8(void *object, u8 enabled);
extern void func_080075CC(struct Tween080EB514 *tween, s16 start, u16 mode,
                          s16 end, u16 duration);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern u8 func_080EB410(struct Runtime080EB514 *runtime);

/* Complete [0x080EB514, 0x080EB740): 556 bytes, 239 instructions. */
u32 func_080EB514(void *context, struct Command080EB514 *command,
                  struct Runtime080EB514 *runtime)
{
    switch (command->state) {
    case 0:
        runtime->script = func_080DFD8C(data_08398FCC, 3, 4, 0, context);
        break;
    case 1:
        break;
    case 0x100: {
        u16 i;

        for (i = 0; i < 10; i++) {
            const struct Entry080EB514 *entries = data_08398F24;
            const struct Entry080EB514 *entry = &entries[i];

            if (runtime->time == entry->time) {
                if (entry->type == 0) {
                    u16 slot = func_080D5FA4(runtime->objects, 8);

                    runtime->objects[(s16)slot] = func_080D5CC0(data_084F7B24,
                        entry->id, entry->x, entry->y, 0x34D, 7, 0, 0);
                    func_080110F8(runtime->objects[(s16)slot], 1);
                    func_080112CC(runtime->objects[(s16)slot], 0x800, 0x800, 0);
                    func_080112E8(runtime->objects[(s16)slot], 1);
                    func_080075CC(&runtime->effects[(s16)slot].x, entry->x, 0, entry->end_x,
                                  entry->duration);
                    func_080075CC(&runtime->effects[(s16)slot].y, entry->y, 0, entry->end_y,
                                  entry->duration);
                    func_080075CC(&runtime->effects[(s16)slot].scale, 0x800, 0, 0x80,
                                  entry->duration);
                    runtime->effects[(s16)slot].state = 0;
                    runtime->effects[(s16)slot].delay = entry->delay;
                } else if (entry->type == 1) {
                    runtime->operation = func_080D6098(0, 0, 0, 0, 2,
                        runtime->parameters, data_08398EDC, context);
                    runtime->event = func_080DFD8C(data_08398FE4, 1, 4, 0,
                                                  context);
                } else {
                    runtime->overlay = func_080D5CC0(data_084F7B24, entry->id,
                        entry->x, entry->y, 0x34D, 7, 0, 0);
                    func_080110F8(runtime->overlay, 1);
                    func_080112CC(runtime->overlay, 0x800, 0x800, 0);
                    func_080112E8(runtime->overlay, 1);
                    func_080075CC(&runtime->scale, 0x800, 0, 0x80,
                                  entry->duration);
                    runtime->state = 0;
                }
            }
        }
        runtime->time++;
        func_080EB410(runtime);
        if (runtime->overlay != 0)
            command->state++;
        break;
    }
    case 0x101:
        if (func_080EB410(runtime))
            command->state = 2;
        break;
    }
    return 0;
}
