/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080717CC.c
 * Original SHA-256: 5d3117849c6ac674caded9ba68cfcffa514c3fc5c5132c4d61401a496d94a7af
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Unit;

typedef struct {
    u8 unknown_000[0x434];
    u8 value;
    u8 palette;
    u8 unknown_436[4];
    u8 mode;
    u8 unknown_43B[9];
    void *resource;
    u32 *instance;
} DisplayContext;

extern DisplayContext *data_03002818;
extern u16 func_08022238(void *unit, u8 *palette);
extern void func_08021BD4(void *resource, void *instance);
extern u32 *func_08021618(void *resource, void *instance, s32 x, s32 y,
                         u32 value, u32 first, u32 second);
extern u8 func_08071704(Unit *unit, u8 selector);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);

/* Complete [0x080717CC, 0x08071888): 188 bytes, 80 instructions. */
void func_080717CC(Unit *unit, u32 first, u8 mode)
{
    if (data_03002818->instance != 0) {
        data_03002818->mode = mode;
        data_03002818->value = func_08022238(unit,
                                           &data_03002818->palette);
        func_08021BD4(data_03002818->resource, data_03002818->instance);
        data_03002818->instance = func_08021618(data_03002818->resource,
                                              0, 0, 20,
                                              data_03002818->value,
                                              first, 0);
        func_08071704(unit, (unit->flags >> 15) ^ 1);
        func_08021DE4(data_03002818->instance, 0, 2);
    }
}
