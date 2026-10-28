/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C8A24.c
 * Original SHA-256: 5c20f4e8a0b7b593c005106064afaa1bf512060b1e4202e9444cc523d0b07ec5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 race;
    u8 unknown_07[0x39];
    u8 ability_points[1];
} Unit080C8A24;

typedef struct {
    u8 unknown_00[6];
    u8 type;
    u8 required_points;
} Ability080C8A24;

extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern const u8 data_085231A4[][2][2];
extern s32 func_080C7EA4(const void *unit, u32 selector);
extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern u8 func_080C9540(u16 flag);
extern void func_080C9574(u16 flag, u16 enabled);
extern const Ability080C8A24 *func_080CD480(u8 race, u8 ability);

/* Complete target: [0x080C8A24, 0x080C8C22), 510 bytes. */
u8 func_080C8A24(Unit080C8A24 *unit, u8 *output)
{
    u8 required;
    u8 satisfied;
    s32 unlocked;
    s32 job;
    s32 count = 0;
    s32 flag;

    g_callbacks_0836D4B8[0](output, 12);
    switch ((u32)func_080C7EA4(unit, 1)) {
    case 12:
        func_080C9574(0x26, 1);
        break;
    case 9:
    case 10:
    case 0x5E:
        return 0;
    }

    for (job = 0x2B, flag = 0x2E; job > 1; job--, flag--) {
        u8 race = func_080C8570(job, job, 1);
        unlocked = 0;

        if (race == unit->race) {
            const u8 (*requirements)[2];
            s32 index;

            if (func_080C9540(flag)) {
                *output = job;
                unlocked = 1;
            }
            requirements = data_085231A4[func_080C8570(job, job, 0x27)];
            required = 0;
            satisfied = 0;
            for (index = 0; index < 2; index++) {
                if (requirements[index][0] != 0)
                    required++;
            }
            if (required == 0) {
                func_080C9574(flag, 1);
                *output++ = job | (s8)0x80;
                count++;
            } else {
                for (index = 0; index < 2; index++) {
                    u8 prerequisite = requirements[index][0];
                    u8 first;
                    u8 last;
                    s32 mastered;
                    s32 ability;

                    if (prerequisite == 0)
                        break;
                    first = func_080C8570(prerequisite, prerequisite, 0x25);
                    last = func_080C8570(prerequisite, prerequisite, 0x26);
                    mastered = 0;
                    for (ability = first; ability <= last; ability++) {
                        if (func_080CD480(unit->race, ability)->type == 1) {
                            u8 points = unit->ability_points[ability] & 0x7F;
                            if (points >= func_080CD480(unit->race, ability)->required_points)
                                mastered++;
                        }
                    }
                    if (mastered >= requirements[index][1])
                        satisfied++;
                    else
                        break;
                }
                if (required != 0 && required == satisfied) {
                    func_080C9574(flag, 1);
                    *output++ = job | (s8)0x80;
                    count++;
                } else if (unlocked) {
                    *output++ = job;
                    count++;
                }
            }
        }
    }
    return count;
}
