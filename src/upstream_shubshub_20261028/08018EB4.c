/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018EB4.c
 * Original SHA-256: 4d42a4b3d0db37e63af114b0886a874faf228df94d044db6f32e23e436f2d0aa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08018EB4..0x08018FF0: 316 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
} SelectedResource;

typedef struct {
    SelectedResource *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];

extern u32 func_080CE4DC(u16 id, u32 field);
extern const u8 *func_080CB524(u32 id);
extern u16 func_08018C24(u8 *destination, const u8 *text);
extern u16 func_08018C94(u8 *destination, u32 format);

#define CURRENT_RESOURCE_ID \
    (g_state_020020D0.current \
        ? g_state_020020D0.current->id : g_state_020020D0.id)

u32 func_08018EB4(u8 *destination, u8 code)
{
    u8 *cursor = destination;
    u32 field = 42;
    u16 resource;

    switch (code) {
    case 0x16:
    case 0x24:
        field = 42;
        break;
    case 0x17:
    case 0x25:
        field = 44;
        break;
    }

    resource = func_080CE4DC(CURRENT_RESOURCE_ID, field);
    if (resource == 0) {
        func_08018C24(cursor, g_table_08526680[0]);
    } else {
        u16 format = 0;
        u32 secondary = 0;

        switch (code) {
        case 0x24:
            secondary = 42;
            break;
        case 0x25:
            secondary = 44;
            break;
        }
        if (secondary != 0)
            format = func_080CE4DC(CURRENT_RESOURCE_ID, secondary);

        if (format != 0)
            cursor += func_08018C94(cursor, 3);
        cursor += func_08018C24(cursor, func_080CB524(resource));

        if (secondary != 0 &&
            func_080CE4DC(CURRENT_RESOURCE_ID, secondary + 1) != 0)
            cursor += func_08018C24(cursor, g_table_085567F0[66]);

        if (format != 0)
            func_08018C94(cursor, 0);
    }
    return 0;
}
