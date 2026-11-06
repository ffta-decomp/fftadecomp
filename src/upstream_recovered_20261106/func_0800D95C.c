/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0800D95C.c
 * Original SHA-256: 57e5ce6f7ca3371608bc20938632e0bcf7cfecad1201113817ffdfaabc41c328
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
/* 0x0800D95C: complete 132-byte owner. */
#include "ffta.h"

struct Object0800C614 {
    u8 unknown_00[0x10];
    u16 active;
    void *data;
};

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} Struct0800C64C;

void *func_0800C614(const struct Object0800C614 *object);
void func_0800C64C(Struct0800C64C *object);
void func_0814186C(const void *source, void *destination, u32 control);

void func_0800D95C(void *object, u8 mode, u8 row, u8 column, u8 count,
                   u16 value)
{
    u16 *destination = 0;
    u16 fill;

    switch (mode) {
    case 0:
        destination = func_0800C614(object);
        break;
    case 1:
        destination = (u16 *)func_0800C614(object) + row * 160;
        break;
    case 2:
        destination = (u16 *)func_0800C614(object) + row * 160;
        break;
    }
    fill = value;
    func_0814186C(&fill, destination + column, 0x01000000 | count);
    func_0800C64C(object);
}
