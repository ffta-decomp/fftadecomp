/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0808AC34.c
 * Original SHA-256: 5a8e86d4f7104288bc6aa831874a47c2c14a4ed671e460e61bac84806dc2371c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 hidden : 1;
    u8 mode : 3;
    u8 unknown_04 : 4;
    u8 unknown_04_bytes[4];
    u16 source_offset;
    u16 destination_offset;
    u8 unknown_0c[4];
    u16 *first_destination;
    u16 *second_destination;
    const u16 *first_source;
    const u16 *second_source;
    u8 unknown_20[8];
    u8 source_stride;
    u8 unknown_29[15];
    s8 clipped_width;
    s8 clipped_height;
    u8 unknown_3a[0x12];
} Tilemap0808AC34;

extern Tilemap0808AC34 data_030009E0[];
extern s32 func_08000F48(const void *source, void *destination, u16 count);

/* Complete target [0x0808AC34, 0x0808ADD4), 416 bytes. */
void func_0808AC34(u32 index)
{
    const u16 *first_source, *second_source;
    u16 *first_destination, *second_destination;
    s32 height;
    if (data_030009E0[index].hidden || data_030009E0[index].clipped_width == 0)
        return;

    if ((data_030009E0[index].mode & 3) == 0) {
        first_source = data_030009E0[index].first_source + data_030009E0[index].source_offset;
        second_source = data_030009E0[index].second_source + data_030009E0[index].source_offset;
        first_destination = data_030009E0[index].first_destination + data_030009E0[index].destination_offset;
        second_destination = data_030009E0[index].second_destination + data_030009E0[index].destination_offset;
        height = data_030009E0[index].clipped_height;

        while (height != 0) {
            func_08000F48(first_source, first_destination, data_030009E0[index].clipped_width);
            first_destination += 32;
            first_source += data_030009E0[index].source_stride;
            func_08000F48(second_source, second_destination, data_030009E0[index].clipped_width);
            second_destination += 32;
            second_source += data_030009E0[index].source_stride;
            height--;
        }
    } else if ((data_030009E0[index].mode & 3) == 1) {
        second_source = data_030009E0[index].second_source + data_030009E0[index].source_offset;
        second_destination = data_030009E0[index].second_destination + data_030009E0[index].destination_offset;
        height = data_030009E0[index].clipped_height;

        while (height != 0) {
            func_08000F48(second_source, second_destination, data_030009E0[index].clipped_width);
            second_destination += 32;
            second_source += data_030009E0[index].source_stride;
            height--;
        }
    } else if ((data_030009E0[index].mode & 3) == 2) {
        first_source = data_030009E0[index].first_source + data_030009E0[index].source_offset;
        first_destination = data_030009E0[index].first_destination + data_030009E0[index].destination_offset;
        height = data_030009E0[index].clipped_height;

        while (height != 0) {
            func_08000F48(first_source, first_destination, data_030009E0[index].clipped_width);
            first_destination += 32;
            first_source += data_030009E0[index].source_stride;
            height--;
        }
    }
}
