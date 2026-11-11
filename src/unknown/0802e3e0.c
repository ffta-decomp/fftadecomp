/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0802E3E0.c
 * Original SHA-256: a0aad9a948d4d753a03b0174a06913a8888ea918f93895bb02d35a57ed266bea
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u16 x;
    u16 y;
    u8 unknown_04[3];
    u8 count;
    u8 final_row;
    u8 unknown_09[0x45c];
    u8 total;
    u8 cursor;
    u8 unknown_467[0x35];
    u16 rows[1][0x34];
} TransferState0802E3E0;

typedef struct {
    u8 unknown_00[0x14];
    u32 map;
} MapState0802E3E0;

extern TransferState0802E3E0 *data_0200F444;
extern MapState0802E3E0 data_030008B0;
extern MapState0802E3E0 data_03000990;
extern u16 data_083C4B44[];
extern u16 data_083C4B10[];

u16 func_080161A0(u8 x, u8 y, u8 stride);
void *func_0802DFCC(void);
void func_08000BAC(void *request, u32 source, u32 destination,
                   u16 count, u16 rows, u16 source_stride, u16 destination_stride);
void func_08000A98(void *request, const void *source, void *destination, u16 count);
void func_0802E08C(u32 row, u8 value);

u8 func_0802E3E0(void)
{
    u8 base_y = data_0200F444->y + 2;
    u32 source = (u32)data_083C4B44;
    u32 destination;

    destination = data_03000990.map +
        func_080161A0(data_0200F444->x,
                       (u8)(data_0200F444->cursor * 2 + base_y), 0x20) * 2;
    func_08000BAC(func_0802DFCC(), source, destination, 0x1a, 2, 0x34, 0x40);

    source = (u32)data_0200F444->rows[data_0200F444->cursor];
    destination = data_030008B0.map +
        func_080161A0((u8)(data_0200F444->x + 1),
                       (u8)(data_0200F444->cursor * 2 + base_y), 0x20) * 2;
    func_08000BAC(func_0802DFCC(), source, destination, 0x1a, 2, 0x34, 0x40);

    if (data_0200F444->cursor < data_0200F444->count)
        func_0802E08C(data_0200F444->cursor, 1);
    if (++data_0200F444->cursor == data_0200F444->total) {
        source = (u32)data_083C4B10;
        destination = data_03000990.map +
            func_080161A0(data_0200F444->x,
                           (u8)(data_0200F444->final_row * 2 + base_y), 0x20) * 2;
        func_08000A98(func_0802DFCC(), (const void *)source, (void *)destination, 0x1a);
        return 1;
    }
    return 0;
}
