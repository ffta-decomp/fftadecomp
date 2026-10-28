#include "interfaces-layout.h"
void RefreshModeRandomStateAndUnitReferences(u8 mode) __asm__("CoreDependency29_000CEA80");
void RefreshModeRandomStateAndUnitReferences(u8 mode)
{
    u32 seed = (s16)NextRandom15();
    seed |= NextRandom15() << 16;
    if (mode != 0) {
        struct ModeRandomState *state = &gModeRandomState;
        u8 *unit;
        u32 count;
        state->active_seed = seed;
        if (NextRandom15() & 1)
            SetGameFlag(0x5a5, 1);
        /* Original save-region-relative base of the primary unit roster. */
        unit = (u8 *)((u32)state - 0x2050);
        count = gContentBank.unit_count;
        if (count != 0) {
            u32 remaining = count;
            do {
            if (((const struct UnitCategoryRecord *)0x085273d8)[ReadUnitField(unit, 1)].category == 0)
                AssignUnitReferenceAvoidingRosterDuplicates(unit);
            --remaining;
            /* Original caller-saved r0 materializes the264-byte roster stride. */
            __asm__ volatile ("mov r0, #132\n\tlsl r0, r0, #1\n\tadd %0, %0, r0"
                              : "+r" (unit) : : "r0", "cc");
            } while (remaining != 0);
        }
    } else {
        gModeRandomState.other_seed = seed;
        if (NextRandom15() & 1)
            SetGameFlag(0x5a6, 1);
    }
}
