/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0806F7B8.c
 * Original SHA-256: 97f3e8d34217e3cb11c426d9e8d2e19fc21d7c65361ae7e1199fc63be381433a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 height;
    u8 unknown_0E[6];
    const void *data;
} Image;

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} Window;

typedef struct {
    u8 unknown_00[8];
    u16 *cursor;
    const void *content;
    u8 unknown_10[2];
    u8 remaining;
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 next_row;
    u16 second;
    u8 unknown_1A[2];
    u16 first;
    u8 pitch;
    u8 setting;
} TextRecord;

typedef struct {
    u8 state;
    u8 active;
    u8 flags[3];
    u8 unknown_05;
    u16 id;
    Window window;
    TextRecord text;
    u8 unknown_54[0x28];
    u32 value;
    u8 unknown_80[4];
    const Image *first_image;
    const Image *second_image;
    u16 text_buffer[234];
} Menu;

typedef struct {
    u8 unknown_00[0x0C];
    u8 pitch;
    u8 unknown_0D[7];
    u16 *tiles;
} Display;

extern Display data_030008B0;
extern u8 *data_0200F428;
extern void func_0806FFE4(const Image *image, void *destination);
extern void func_08017424(Window *window, u32 first, u32 second,
                         u8 x, u8 y, u8 width, u8 height, u16 value,
                         u8 setting, u16 first_value, u16 second_value,
                         u8 final_setting);
extern void func_08017528(TextRecord *record, u16 *source,
                         const void *content, u8 x, u8 y, u8 width,
                         u8 height, u8 pitch, u16 first, u8 setting,
                         u16 second);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0806FABC(void *state, u16 id);
extern void func_0806FB50(void *state, u16 id);

/* Complete target [0x0806F7B8, 0x0806F8DC): 292 bytes. */
void func_0806F7B8(Menu *menu, u16 first, u32 value,
                   const Image *first_image, const Image *second_image,
                   u16 id, u8 x, u8 y)
{
    u16 zero;
    u8 i;

    menu->first_image = first_image;
    menu->second_image = second_image;
    func_0806FFE4(menu->first_image, (u8 *)menu + 0x260);
    func_0806FFE4(menu->second_image, (u8 *)menu + 0xA60);
    menu->value = value;
    menu->id = id;
    func_08017424(&menu->window, (u32)menu->first_image->data,
                 (u32)menu->second_image->data, x, y, 13, 18, 0,
                 data_030008B0.pitch, 5, 1, 11);
    func_08017528(&menu->text, data_030008B0.tiles, menu->text_buffer,
                 x, y, 13, 9, data_030008B0.pitch, first,
                 menu->window.field_17, 0);
    zero = 0;
    func_0814186C(&zero, menu->text_buffer, 0x010000EA);
    menu->active = 0;
    func_0806FABC(data_0200F428 + 0x1A88, menu->id);
    func_0806FB50(data_0200F428 + 0x1A88, menu->id);
    for (i = 0; i < 3; ++i)
        menu->flags[i] = 0;
    menu->state = 0;
}
