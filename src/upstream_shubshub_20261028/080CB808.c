/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CB808.c
 * Original SHA-256: 6f378728760575fbe2c1b1671f63be54f3aa1efc77dc58cc0ad57d0f519c8521
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 type;
} Unit;

typedef struct {
    u8 unknown_00[11];
    u8 text_index;
    u8 unknown_0C[2];
} __attribute__((packed)) UnitTypeInfo;

extern const u8 data_083E105C[];
extern const UnitTypeInfo g_table_085273D8[];
extern u8 func_080C817C(Unit *unit);
extern u32 func_080C92F0(Unit *unit, u32 field);
extern const u8 *func_080071A8(const void *resource, u8 index);
extern const u8 *func_0800588C(const u8 *text);

const u8 *func_080CB808(Unit *unit)
{
    const void *resource = data_083E105C;
    u32 index;

    if (func_080C817C(unit)) {
        const UnitTypeInfo *type_info = &g_table_085273D8[unit->type];
        index = type_info->text_index;
    } else {
        index = func_080C92F0(unit, 9);
    }
    return func_0800588C(func_080071A8(resource, index));
}
