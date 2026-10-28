/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801984C.c
 * Original SHA-256: d3fd164ffd92ace2f2092c46329ddcaea62f3d852c5bff7b0d234208f4933d81
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801984C..0x080198D4: 136 bytes. */
typedef struct {
    u8 unknown_00[4];
    u8 selection[2];
} SelectionState;

typedef struct {
    u8 unknown_00[7];
    u8 flags;
    u8 unknown_08[8];
} SelectionEntry;

extern SelectionState *g_state_020020D0;
extern const SelectionEntry g_table_08521214[];
extern const u8 *const data_08391850[];
extern u16 func_08018C24(u8 *, const u8 *);

static inline u8 selection_slot(u8 code)
{
    return code != 0x49;
}

int func_0801984C(u8 *destination, u8 code)
{
    const SelectionState *state = g_state_020020D0;
    u8 *cursor = destination;
    u8 slot = selection_slot(code);
    const u8 *selections = state->selection;
    u8 selection = selections[slot];

    if (selection) {
        const SelectionEntry *entry = &g_table_08521214[selection];

        if (entry->flags) {
            int index = 0;
            const u8 *const *strings = data_08391850;
            const u8 *const *text = strings;

            for (; index < 8; text++, index++) {
                if ((entry->flags >> index) & 1) {
                    cursor += func_08018C24(cursor, *text);
                    cursor += func_08018C24(cursor, strings[8]);
                }
            }
            cursor[-2] = 0;
        }
    }
    return 0;
}
