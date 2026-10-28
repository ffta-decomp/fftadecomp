/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08067CF8.c
 * Original SHA-256: 18db0221b0d88c1d8e09727a9827e48e81d7b93b27c3cb84ff4c4c1a215a533b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} Cursor08067CF8;

typedef struct {
    u8 unknown_00[0x10];
    void *owner;
    u8 unknown_14[0x3c];
    u8 list[0x20];
    Cursor08067CF8 cursor;
    u8 settings[1];
} Object08067CF8;

extern void func_08017FBC(void *, u32);
extern void func_08017FB0(Cursor08067CF8 *, u8);
extern void func_080676F8(Object08067CF8 *, s16);
extern void func_08017884(void *, u32, u32);
extern void func_08067E48(Object08067CF8 *, u8, u32);
extern void func_08066C28(Object08067CF8 *);

/* 0x08067CF8..0x08067D6A: 114 bytes, 51 instructions. */
void func_08067CF8(Object08067CF8 *object, u8 option, u8 row, u8 refresh)
{
    Cursor08067CF8 *cursor = &object->cursor;
    u8 *settings = object->settings;
    u8 *list = object->list;
    s32 selected;

    func_08017FBC(settings, option);
    selected = row;
    if (!refresh) {
        func_08017FB0(cursor, (u8)selected);
    } else {
        func_080676F8(object, (s8)selected);
        func_08017884(list, option, 1);
    }
    func_08067E48(object, cursor->row, 0);
    if (object->owner)
        func_08066C28(object);
}
