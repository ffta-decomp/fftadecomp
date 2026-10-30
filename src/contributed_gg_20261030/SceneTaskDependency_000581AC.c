/* Contributed by gg; original source and attribution follow. */
asm(".global f_080583C8\n.thumb_set f_080583C8,0x080583C9\n.global f_0805872C\n.thumb_set f_0805872C,0x0805872D\n");
/* SceneTaskDependency_000581AC
   entry 0x080581AC, 412 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08053FE0.c
 * Original SHA-256: 442da4e769e6d6e6a19aecd092ed6bfb937e42bbb4758d9e5772be36fceedc4e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* ---- inlined ffta.h ---- */
#ifndef FFTA_SHIM_H
#define FFTA_SHIM_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
#endif

typedef struct {
    u8 unknown_00[0x00000018];
    s16 count;
    s16 top;
} ScrollList08053FE0;

typedef struct {
    u8 unknown_00[0x0E];
    u16 offset;
    u8 unknown_10;
    u8 row;
} MenuCursor08053FE0;

typedef struct {
    u8 unknown_00[0x0000002C];
    ScrollList08053FE0 list;
    u8 unknown_48[4];
    MenuCursor08053FE0 cursor;
    u8 unknown_60[1];
} Menu08053FE0;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input08053FE0;

typedef struct {
    void (*callback)(void *);
    void *context;
    u16 keys;
} KeyBinding08053FE0;

extern Input08053FE0 data_03000000;
extern void func_080023D0(Input08053FE0 *input);
extern void func_08141540(u32 sound);
extern void f_0805872C(MenuCursor08053FE0 *cursor, u8 row);
extern u8 f_080583C8(ScrollList08053FE0 *list, u16 keys);
extern void func_08017FBC(void *context, u16 keys);

/* Complete target: [0x08053FE0, 0x080583C8), 412 bytes. */
void f_target(Menu08053FE0 *menu, void (*scroll)(void *),
                   void *scroll_context, u8 row_count,
                   KeyBinding08053FE0 *bindings, u8 binding_count)
{
    s8 row;
    s8 index;

    if (row_count > 3) {
        if (data_03000000.repeated & 0x00000080) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row + 1;
            if (row <= 2) {
                func_08141540(0x0000006D);
                f_0805872C(&menu->cursor, row);
                func_08017FBC(menu->unknown_60, 0x00000080);
            } else if (f_080583C8(&menu->list, 0x00000080)) {
                func_08141540(0x0000006D);
                scroll(scroll_context);
                func_08017FBC(menu->unknown_60, 0x00000080);
            }
        }
        if (data_03000000.repeated & 0x00000040) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row - 1;
            if (row >= 0) {
                func_08141540(0x0000006D);
                f_0805872C(&menu->cursor, row);
            } else if (f_080583C8(&menu->list, 0x00000040)) {
                func_08141540(0x0000006D);
                scroll(scroll_context);
            } else {
                goto dispatch;
            }
            func_08017FBC(menu->unknown_60, 0x00000040);
        }
    } else {
        if (data_03000000.repeated & 0x00000080) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row + 1;
            if (row > row_count - 1)
                row = row_count - 1;
            else
                func_08141540(0x0000006D);
            f_0805872C(&menu->cursor, row);
        } else if (data_03000000.repeated & 0x00000040) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row - 1;
            if (row < 0)
                row = 0;
            else
                func_08141540(0x0000006D);
            f_0805872C(&menu->cursor, row);
        }
    }

dispatch:
    for (index = 0; index < binding_count; index++) {
        if (data_03000000.pressed & bindings[index].keys)
            bindings[index].callback(bindings[index].context);
    }
}
