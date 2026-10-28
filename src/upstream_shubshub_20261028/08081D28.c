/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08081D28.c
 * Original SHA-256: d62a40a04e684c50a70a58142ef4d466e3b1b279da877d9f6562a33a2420420a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 scroll;
    u32 unknown_1C;
} MenuList;

typedef struct {
    u32 unknown_00;
    void *owner;
    u16 field_08;
    u16 field_0A;
    u16 field_0C;
    u16 position;
    u8 flags;
    u8 row;
    u8 field_12;
} MenuCursor;

typedef struct {
    u8 unknown_00[0x20];
} MenuAnimation;

typedef struct {
    u8 unknown_00[0x36];
    u8 selected;
    u8 unknown_37[0x41];
    MenuList list;
    MenuCursor cursor;
    MenuAnimation animation;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x2C88];
    MenuRecord records[0];
} MenuState;

extern MenuState *data_03002818;
extern void func_08017FBC(MenuAnimation *animation);
extern void func_08017FB0(MenuCursor *cursor, u8 row);
extern u16 func_08017B68(MenuList *list, u32 row);
extern void func_080819F0(u32 index, s8 row, MenuList *list);
extern void func_08017884(MenuList *list, u32 option, u32 enabled);

/* Complete target: [0x08081D28, 0x08081DEC), 196 bytes, 82 instructions. */
void func_08081D28(u32 index, u8 option, u8 row, u8 refresh)
{
    u32 requested_row = row;
    MenuState **state = &data_03002818;

    func_08017FBC(&(*state)->records[index].animation);
    if (refresh == 0) {
        func_08017FB0(&(*state)->records[index].cursor, (u8)requested_row);
        (*state)->records[index].selected =
            func_08017B68((MenuList *)(index * sizeof(MenuRecord) + (u32)*state + 0x2D00), (s8)requested_row);
    } else {
        func_080819F0(index, (s8)requested_row, &(*state)->records[index].list);
        (*state)->records[index].selected =
            func_08017B68((MenuList *)(index * sizeof(MenuRecord) + (u32)*state + 0x2D00), (s8)requested_row);
        func_08017884(&(*state)->records[index].list, option, 1);
    }
}
