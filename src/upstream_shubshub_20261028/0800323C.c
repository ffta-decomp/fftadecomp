/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800323C.c
 * Original SHA-256: 5f44f6f5a4b239d47561473a924959905c8e8fa6cf8565742ff134808ec4fded
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800323C - 116 bytes. Initialize the four display register records. */
typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    void *destination;
} Display0800323C;

extern Display0800323C data_03000E60;
extern Display0800323C data_03000E80;
extern Display0800323C data_030008B0;
extern Display0800323C data_03000990;
extern u16 data_03000942[];

void func_0800323C(void)
{
    data_03000E60.control = &data_03000942[0];
    data_03000E60.horizontal_offset = &data_03000942[4];
    data_03000E60.vertical_offset = &data_03000942[5];
    data_03000E60.unknown_0c = 0;
    data_03000E60.unknown_0d = 0;
    data_03000E60.tiles = 0;
    data_03000E60.destination = 0;

    data_03000E80.control = &data_03000942[1];
    data_03000E80.horizontal_offset = &data_03000942[6];
    data_03000E80.vertical_offset = &data_03000942[7];
    data_03000E80.unknown_0c = 0;
    data_03000E80.unknown_0d = 0;
    data_03000E80.tiles = 0;
    data_03000E80.destination = 0;

    data_030008B0.control = &data_03000942[2];
    data_030008B0.horizontal_offset = &data_03000942[8];
    data_030008B0.vertical_offset = &data_03000942[9];
    data_030008B0.unknown_0c = 0;
    data_030008B0.unknown_0d = 0;
    data_030008B0.tiles = 0;
    data_030008B0.destination = 0;

    data_03000990.control = &data_03000942[3];
    data_03000990.horizontal_offset = &data_03000942[10];
    data_03000990.vertical_offset = &data_03000942[11];
    data_03000990.unknown_0c = 0;
    data_03000990.unknown_0d = 0;
    data_03000990.tiles = 0;
    data_03000990.destination = 0;

}
