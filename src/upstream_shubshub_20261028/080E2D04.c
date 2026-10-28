/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E2D04.c
 * Original SHA-256: 4e9dccebffb9e5b4ee0a6f596217a0df4fd79024bb39d7e24b6f03ba50e4e6bf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Command080E2D04 {
    u16 state;
};

struct Runtime080E2D04 {
    void *object;
    void *child;
};

struct Global080E2D04 {
    u8 unknown_00[0xC2];
    u16 value;
};

struct Resource080E2D04 {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed));

extern const u8 data_08395E9C[];
extern struct Global080E2D04 data_03003860;
extern const struct Resource080E2D04 data_088F38BC;
extern u16 g_control_flags_03000940;

extern void *func_080D7A70(const void *data, u32 count, void *context);
extern void *func_080D7ABC(void *child);
extern void func_080D4D14(void *object, u32 value);
extern void func_080D49FC(u32 first, u32 second, u32 third, u32 fourth, u32 fifth);
extern void func_0800BCE0(u32 first, u32 second);
extern void func_0800BC4C(u32 first, u32 second);
extern void *func_0800B47C(u8 group, const void *data, const void *extra,
                          u8 first, u8 second);
extern void func_0800BEDC(void *object, u8 mode);
extern void func_0800BED8(void *object, s16 value);
extern void func_0800BF04(void *object, u8 first, u8 second);
extern void func_0800BE78(void *object, s16 x, s16 y, u16 width, u16 height);
extern void func_0800BDD0(void *object, u8 enabled);
extern u32 func_080035A8(u16 value);
extern u32 func_080D4D08(void *object);

/* Complete [0x080E2D04, 0x080E2E24): 288 bytes, 120 instructions. */
u32 func_080E2D04(void *context, struct Command080E2D04 *command,
                  struct Runtime080E2D04 *runtime)
{
    switch (command->state) {
    case 0:
        runtime->child = func_080D7A70(data_08395E9C, 1, context);
        data_03003860.value = 0;
        break;
    case 1:
        func_080D4D14(runtime->object, 0);
        break;
    case 0x100:
        runtime->child = func_080D7ABC(runtime->child);
        if (runtime->child == 0)
            command->state++;
        break;
    case 0x101: {
        const struct Resource080E2D04 *resource;
        u32 flags;
        u16 control;

        func_080D49FC(0, 2, 0, 0, 0);
        func_0800BCE0(0, 0);
        func_0800BC4C(0, 1);
        resource = &data_088F38BC;
        runtime->object = func_0800B47C(0, resource->data,
                                      (const u8 *)resource + resource->offset,
                                      0, 0);
        func_0800BEDC(runtime->object, 6);
        func_0800BED8(runtime->object, 0x260);
        func_0800BF04(runtime->object, resource->flags & 4, resource->flags & 8);
        func_0800BE78(runtime->object, 0, 0, 30, 20);
        func_0800BDD0(runtime->object, 1);
        flags = func_080035A8(2);
        control = g_control_flags_03000940;
        control |= flags;
        g_control_flags_03000940 = control;
        command->state++;
        break;
    }
    case 0x102:
        if (func_080D4D08(runtime->object))
            command->state = 2;
        break;
    }
    return 0;
}
