/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08071704.c
 * Original SHA-256: 17246baf3e746794ded7ff142715cc344c6a013d67cb06153777ab9b4109a91f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 index;
} Unit08071704;

typedef struct {
    u8 unknown_00[8];
    u16 first_slot : 4;
    u16 first_resource : 8;
    u16 second_slot : 4;
    u8 second_resource;
    u8 unknown_0B[3];
} __attribute__((packed)) PaletteEntry08071704;

typedef void (*BufferCopier08071704)(void *destination, const void *source,
                                    u32 size);

extern const PaletteEntry08071704 g_table_085273D8[];
extern BufferCopier08071704 data_0836D4BC[];
extern u8 *data_03002818;
extern u8 func_080C817C(void *unit);
extern const u8 *func_080CBB7C(u8 index);
extern u32 func_080C92F0(void *unit, u32 selector);

/* Complete [0x08071704, 0x080717CC): 200 bytes, 83 instructions. */
u8 func_08071704(Unit08071704 *unit, u8 selector)
{
    if (func_080C817C(unit)) {
        const PaletteEntry08071704 *entry = &g_table_085273D8[unit->index];

        if (selector == 1) {
            if (entry->first_resource != 0) {
                data_0836D4BC[0](data_03002818 + 0x228 +
                                 (entry->first_slot << 5),
                                 func_080CBB7C(entry->first_resource - 1), 32);
            }
            return entry->first_slot;
        } else {
            if (entry->second_resource != 0) {
                data_0836D4BC[0](data_03002818 + 0x228 +
                                 (entry->second_slot << 5),
                                 func_080CBB7C(entry->second_resource - 1), 32);
            }
            return entry->second_slot;
        }
    } else {
        u32 field = 7;

        if (selector == 1)
            field = 6;
        return func_080C92F0(unit, field);
    }
}
