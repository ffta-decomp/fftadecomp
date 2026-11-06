/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08055C38.c
 * Original SHA-256: f81081267b59d0eb0ca7931bdda1f6701504c836690e5aa989451799bc966397
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* Complete 0x08055C38..0x08055DC4, 396 bytes, 143 reached instructions.
 * Target: f0b54f464646c0b482b00006000e80460906090e8946194f38681949461801a900200880f168727db07d4243520080204004024301a8ebf0fdfdfef753fc3968104a9446614408703b680f481d180f495c180f4801690f48401a002800da1f30c202120c614658180378281c211cc0f7b3fa424672830024454621e028f40002bc140000522d00009014000004150000b008000300c0000638680e4a81180e4a80184019027823061b0e00200090301c01f0f8ff601c0004040c681c0004050c3868064a81180878022809d809788c42e2db07e0c81900003a2d0000522d0000022cd9dd0b4c21680b480918301c002202f07cf8301cd5f7ebf92468074960180078032810d8064aa01806490022c0f707f80fe028f400023a2d0000522d000090140000817e0108124960181249134abff7f6ff124d2868124c00190321c1f7cfff28680019494602f0d4fc28680019417c301c02f0c6fc29680b4a8918087001f026fb02b018bc9846a146f0bc01bc0047000090140000817e0108057f010828f40002dc140000552d0000
 */
typedef struct {
    u8 unknown_00[8];
    u16 *dest;
    u16 *source;
    u8 unknown_10[5];
    u8 width;
    u8 columns;
    u8 count;
    s16 limit;
    u16 position;
    u16 tile;
    u8 stride;
    u8 palette;
} List;

typedef struct {
    u32 unknown_00;
    void *owner;
    u16 x;
    u16 y;
    u16 counter;
    u16 extent;
    u8 flags;
    u8 value;
    u8 field_12;
    u8 unknown_13;
} Controls;

typedef struct Cursor Cursor;
typedef void (*CursorCallback)(Cursor *);
typedef struct {
    u8 unknown_00[0x2C];
    List list;
    Controls controls;
    u8 cursor[0x14];
} Window;

typedef struct {
    u8 unknown_00[0x1490];
    Window window;
    u8 content[0x19C8 - 0x1504];
    u8 text[0x2D3A - 0x19C8];
    u8 entries[24];
    u8 count;
    u8 unknown_2D53[2];
    u8 selected;
} State;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics;
extern State *data_0200F428;
extern Graphics data_030008B0;
extern u8 data_0600C000[];
extern void func_0814186C(const void *source, void *dest, u32 control);
extern u8 func_0805451C(void);
extern void func_08016210(void *window, const void *content, u16 first, u16 second);
extern void func_08057CDC(List *list, void *text, u8 entry, u8 row, u8 mode);
extern void func_08057E24(List *list, const u8 *entries, u8 mode);
extern void func_0802B108(List *list);
extern void func_08015D58(Window *window, u32 value, CursorCallback callback);
extern void func_08017E80(void *object);
extern void func_08017F04(Cursor *object);
extern void func_08017D18(Controls *controls, u8 mask);
extern void func_0805872C(Controls *controls, u8 value);
extern u8 func_0805871C(List *list, u8 value);
extern void func_080573E8(void);

void func_08055C38(u8 position, u8 direction)
{
    List *list = &data_0200F428->window.list;
    u16 fill;
    u16 *fillSource = &fill;
    u16 row;
    u16 entry;

    *fillSource = 0;
    func_0814186C(fillSource, list->source,
                 0x01000000 | (list->width * list->columns * 2));
    data_0200F428->count = func_0805451C();
    func_08016210(&data_0200F428->window, data_0200F428->content,
                 (data_0600C000 - data_030008B0.tiles) / 32,
                 data_0200F428->count);
    list->position = position;
    for (row = 0, entry = position;
         row < (data_0200F428->count < 3 ? data_0200F428->count : 3);
         row++, entry++) {
        func_08057CDC(list, data_0200F428->text,
                     data_0200F428->entries[entry], row, 0);
    }
    func_08057E24(list, data_0200F428->entries, 0);
    func_0802B108(list);
    if (data_0200F428->count <= 3)
        func_08015D58(&data_0200F428->window, (u32)func_08017E80, 0);
    else
        func_08015D58(&data_0200F428->window, (u32)func_08017E80,
                     func_08017F04);
    {
        Controls *controls = &data_0200F428->window.controls;
        func_08017D18(controls, 3);
        controls = &data_0200F428->window.controls;
        func_0805872C(controls, direction);
        controls = &data_0200F428->window.controls;
        data_0200F428->selected = func_0805871C(list, controls->value);
    }
    func_080573E8();
}
