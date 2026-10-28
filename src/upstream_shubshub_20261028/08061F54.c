/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08061F54.c
 * Original SHA-256: b955e47ea16eb8c1a9f8adbea1f441d0d3072883eca31e4ed5f689e9a0ea8ab1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    const void *definition;
    u8 unknown_04[2];
    u8 race;
    u8 unknown_07[0x39];
    u8 ability_points[0xB6];
    u8 status_F6;
    u8 status_F7;
    u8 unknown_F8;
    u8 status_F9;
    u8 status_FA;
    u8 unknown_FB[0xD];
} Unit08061F54;

typedef struct {
    u8 unknown_00[0x5C];
    Unit08061F54 *source;
    Unit08061F54 *destination;
} Owner08061F54;

typedef struct {
    u8 unknown_00[6];
    u8 type;
    u8 required_points;
} Ability08061F54;

extern Owner08061F54 *data_0200F450;
extern Unit08061F54 g_state_02000080[24];
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 bytes);
extern void (*data_0836D4BC)(void *destination, const void *source, u32 bytes);
extern const u8 data_085231A4[][2][2];
extern void func_080CB4C0(void *unit);
extern const void *func_080CA1BC(const void *unit);
extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern u8 func_080C9540(u16 flag);
extern void func_080C9574(u16 flag, u16 enabled);
extern const Ability08061F54 *func_080CD480(u8 race, u8 ability);

/* 0x08061F54..0x0806216A: 534 bytes, 238 instructions. */
void func_08061F54(u8 enabled)
{
    s32 found = 0;
    Unit08061F54 *destination = data_0200F450->destination;
    Unit08061F54 *source = data_0200F450->source;
    Unit08061F54 *unit;
    s32 i;
    s32 job;
    s32 flag;
    u8 required;
    u8 satisfied;

    if (!enabled) {
        for (unit = g_state_02000080, i = 0; i < 24; i++, unit++) {
            if (destination == unit) {
                func_080CB4C0(unit);
                g_callbacks_0836D4B8[0](unit, sizeof(*unit));
                break;
            }
        }
        return;
    }
    for (unit = g_state_02000080, i = 0; i < 24; i++, unit++) {
        if (destination == unit) {
            found = 1;
            break;
        }
    }
    if (!found)
        return;

    func_080C9574(0x3E, 1);
    func_080CB4C0(source);
    func_080C9574(0x3E, 0);
    data_0836D4BC(unit, source, sizeof(*unit));
    unit->status_F7 = 0;
    unit->status_F6 = 0;
    unit->status_FA = 0;
    unit->status_F9 = 0;
    unit->definition = func_080CA1BC(unit);

    for (job = 0x2B, flag = 0x2E; job > 1; job--, flag--) {
        u8 race = func_080C8570(job, job, 1);
        const u8 (*requirements)[2];
        s32 index;

        if (race != unit->race)
            continue;
        if (func_080C9540(flag))
            continue;
        requirements = data_085231A4[func_080C8570(job, job, 0x27)];
        required = 0;
        satisfied = 0;
        for (index = 0; index < 2; index++) {
            if (requirements[index][0] != 0)
                required++;
        }
        if (required == 0) {
            func_080C9574(flag, 1);
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
            if (required != 0 && required == satisfied)
                func_080C9574(flag, 1);
        }
    }
}
