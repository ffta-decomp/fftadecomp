/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08015DAC.c
 * Original SHA-256: bf6d0426adbb81581acdc95644ff3e262c94d7b0a35b9f98a08c05aa178b2602
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08015DAC..0x0801606E: 706 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
    u8 unknown_02[6];
    u16 items[2];
    u16 abilities[2];
} TextResource;

typedef struct {
    TextResource *current;
    u32 selected;
    u32 unknown_08;
    u16 id;
    u16 table_index;
    u8 unknown_10[0xA2];
    u8 category;
    u8 unknown_b3;
    u8 override_category;
} TextSelection;

typedef struct {
    u8 unknown_00[2];
    u8 category;
    u8 unknown_03[13];
} ItemCategory;

typedef struct {
    u8 category;
    u8 unknown_01[3];
} NameCategory;

extern TextSelection g_state_020020D0;
extern const NameCategory data_08528968[];
extern const ItemCategory g_table_08521214[];
extern const ItemCategory data_0851FAA4[];

extern u32 func_080CE4DC(u16 id, u32 field);
extern u8 func_080CEBF8(u8 category);
extern void func_080CB980(void *destination, u32 id);
extern u32 func_080CB99C(u16 id);
extern void func_080CB9B0(void *destination, u32 category);
extern u32 func_080CB9CC(u32 category);
extern u8 func_080C9540(u32 flag);

#define CURRENT_RESOURCE_ID \
    (g_state_020020D0.current \
        ? g_state_020020D0.current->id : g_state_020020D0.id)

u8 func_08015DAC(void *destination, u8 code, u8 *missing)
{
    u8 result = 0;
    u16 id;

    switch (code) {
    case 0:
        {
            u8 category;

            if (g_state_020020D0.override_category) {
                category = func_080CEBF8(g_state_020020D0.category);
            } else {
                category = func_080CE4DC(CURRENT_RESOURCE_ID, 2);
                category += 15;
                if (func_080CE4DC(CURRENT_RESOURCE_ID, 1) == 1)
                    category = 6;
            }
            func_080CB9B0(destination, category);
            result = func_080CB9CC(category);
        }
        break;

    case 1:
        {
            u32 offset = g_state_020020D0.table_index * sizeof(NameCategory);
            const NameCategory *entry = (const NameCategory *)
                ((const u8 *)data_08528968 + offset);

            func_080CB9B0(destination, (u8)(entry->category + 31));
            result = func_080CB9CC(entry->category + 31);
        }
        break;

    case 2:
        func_080CB980(destination, g_state_020020D0.id);
        result = func_080CB99C(g_state_020020D0.id) + 13;
        break;

    case 3:
    case 4:
        {
            u32 selected = g_state_020020D0.selected;
            u32 kind = selected >> 16;
            id = selected;

            switch (kind) {
            case 1:
                {
                    u32 offset = id * sizeof(ItemCategory);
                    const ItemCategory *entry = (const ItemCategory *)
                        ((const u8 *)g_table_08521214 + offset);
                    id = entry->category ? 394 + entry->category : 0;
                }
                break;
            case 2:
                if (id > 85)
                    id = 394;
                else
                    id = 393;
                break;
            }
            func_080CB980(destination, id);
            result = func_080CB99C(id) + 13;
        }
        break;

    case 0x81:
        {
            id = 392;

            func_080CB980(destination, id);
            result = func_080CB99C(id) + 13;
        }
        break;

    case 0x82:
    case 0x83:
        {
            TextResource *current = g_state_020020D0.current;
            u8 slot;
            u32 field;

            if (code == 0x82) {
                slot = 0;
                field = 0x3D;
            } else {
                slot = 1;
                field = 0x3E;
            }
            if (func_080CE4DC(current->id, field)) {
                id = 386;
                func_080CB980(destination, id);
                return func_080CB99C(id) + 13;
            } else {
                u16 item = current->items[slot];

                if (item == 0) {
                    *missing = 1;
                    return 0;
                }
                if (item <= 375) {
                    id = item;
                } else {
                    u32 offset = item * sizeof(ItemCategory);
                    const ItemCategory *entry = (const ItemCategory *)
                        ((const u8 *)data_0851FAA4 + offset);
                    id = entry->category ? 394 + entry->category : 0;
                }
                func_080CB980(destination, id);
                result = func_080CB99C(id) + 13;
            }
        }
        break;

    case 0x84:
    case 0x85:
        {
            TextResource *current = g_state_020020D0.current;
            u8 slot;
            u32 field;

            if (code == 0x84) {
                slot = 0;
                field = 0x3F;
            } else {
                slot = 1;
                field = 0x40;
            }
            if (func_080CE4DC(current->id, field)) {
                id = 386;
                func_080CB980(destination, id);
                return func_080CB99C(id) + 13;
            } else {
                u8 ability = current->abilities[slot];

                if (ability == 0 || !func_080C9540(0x207)) {
                    *missing = 1;
                    return 0;
                }
                id = 393;
                if (ability > 85)
                    id++;
                func_080CB980(destination, id);
                result = func_080CB99C(id) + 13;
            }
        }
        break;

    case 0x86 ... 0x8D:
        {
            id = code - 0x72;

            func_080CB9B0(destination, (u8)id);
            result = func_080CB9CC(id);
        }
        break;

    case 0x8E:
        func_080CB9B0(destination, 18);
        result = func_080CB9CC(18);
        break;
    }
    return result;
}
