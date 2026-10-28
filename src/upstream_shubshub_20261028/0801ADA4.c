/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801ADA4.c
 * Original SHA-256: ce930e081cc1e7f024feab4c1e471d71b5830db6860c2c9210606acc40fe4ed9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801ADA4..0x0801ADE0: 60 bytes. */
typedef struct {
    u8 unknown_00[0xA0];
    u8 *primary;
    u8 unknown_A4[0xB4];
    u8 *objects[4];
} ObjectGroup;

extern ObjectGroup g_state_02007F40;
extern void func_08020F64(u8 *object);

void func_0801ADA4(void)
{
    ObjectGroup *group = &g_state_02007F40;
    u8 **objects;
    u8 index;

    if (group->primary != 0) {
        func_08020F64(group->primary);
    }
    index = 0;
    objects = group->objects;
    do {
        if (objects[index] != 0) {
            func_08020F64(objects[index]);
        }
        index++;
    } while (index < 4);
}
