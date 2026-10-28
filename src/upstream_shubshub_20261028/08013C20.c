/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013C20.c
 * Original SHA-256: 7117b5694028f7e57a58073fe4bee8dda4c3fd2c5a7abda722845856a2c87537
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08013C20..0x08013E9C: 636 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
    u8 flags;
} PackedResource;

typedef struct {
    u8 unknown_00[0x22];
    u8 category;
    u8 unknown_23[5];
} ResourceCategory;

typedef struct {
    PackedResource *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern u8 g_state_02000000[];
extern const ResourceCategory g_table_0854CD54[];
extern u8 data_020078B0[];
extern const u8 data_084EF3F4[];
extern const u8 data_084AADFC[];
extern const u8 data_084A002C[];
extern const u8 data_084B83A0[];

extern u32 func_080CE4DC(u16 id, u32 field);
extern u16 func_0800A024(void);
extern u16 func_08013E9C(u8 *destination, const u8 *table,
                         u8 *workspace, u16 index, u32 first, u32 second);

#define CURRENT_RESOURCE_ID \
    (g_state_020020D0.current \
        ? g_state_020020D0.current->id : g_state_020020D0.id)

u16 func_08013C20(u8 code)
{
    u16 result = 0;

    switch (code) {
    case 0x90 ... 0xAC:
        result = func_08013E9C(data_020078B0, data_084EF3F4,
                               data_020078B0 + 0x200,
                               (u16)(code - 0x90), 0, 0);
        break;

    case 0x80:
        {
            u16 index;
            const u8 *table;

            if (g_state_020020D0.current)
                index = g_state_020020D0.current->id - 1;
            else
                index = g_state_020020D0.id - 1;

            if (index > 199) {
                table = data_084AADFC;
                index -= 200;
            } else {
                table = data_084A002C;
            }
            result = func_08013E9C(data_020078B0, table,
                                   data_020078B0 + 0x200, index, 0, 0);
        }
        break;

    case 0x87:
        {
            u32 id;
            u8 index;

            id = CURRENT_RESOURCE_ID;
            index = func_080CE4DC(id, 0x11);

            if ((g_state_020020D0.current->flags & 0x1C) == 0 && index != 0)
                index += 4;
            result = func_08013E9C(data_020078B0, data_084B83A0,
                                   data_020078B0 + 0x200, index, 0, 0);
        }
        break;

    case 0x13:
        {
            u32 id;
            u8 index;

            id = CURRENT_RESOURCE_ID;
            if (func_080CE4DC(id, 2) == 3) {
                index = 10;
            } else {
                id = CURRENT_RESOURCE_ID;
                if (func_080CE4DC(id, 0x37) != 0)
                    index = 8;
                else
                    index = 9;
            }
            result = func_08013E9C(data_020078B0, data_084B83A0,
                                   data_020078B0 + 0x200, index, 0, 0);
        }
        break;

    case 0x89:
        {
            u32 id;
            u8 index;

            id = CURRENT_RESOURCE_ID;
            index = func_080CE4DC(id, 0x12) + 11;
            result = func_08013E9C(data_020078B0, data_084B83A0,
                                   data_020078B0 + 0x200, index, 0, 0);
        }
        break;

    case 0x55:
        {
            u8 index = 16;
            u16 selection = func_0800A024();
            u32 offset = selection * sizeof(ResourceCategory);
            const ResourceCategory *entry = (const ResourceCategory *)
                ((const u8 *)g_table_0854CD54 + offset);

            switch (entry->category) {
            case 0:
                index = 15;
                break;
            case 1:
                break;
            case 3:
                index = 18;
                break;
            case 2:
                index = 17;
                break;
            }
            result = func_08013E9C(data_020078B0, data_084B83A0,
                                   data_020078B0 + 0x200, index, 0, 0);
        }
        break;

    case 0x56:
        {
            u8 index = 0;

            switch (g_state_02000000[0x3C2A]) {
            case 8:
                index = 20;
                break;
            case 0x31:
            case 0x39:
                index = 19;
                break;
            }
            if (index == 0) {
                result = 3;
                break;
            }
            result = func_08013E9C(data_020078B0, data_084B83A0,
                                   data_020078B0 + 0x200, index, 0, 0);
        }
        break;
    }

    return result - 3;
}
