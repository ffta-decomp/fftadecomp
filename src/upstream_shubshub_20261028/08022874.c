/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022874.c
 * Original SHA-256: 94b76ee67674a218e5219e36e0fb94e946cfc910ee47d81ea9958c569739417e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct DisplayRecord {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 width;
    u8 height;
    u8 *tiles;
    void *destination;
} DisplayRecord;

extern DisplayRecord data_03000E60;
extern DisplayRecord data_03000E80;
extern DisplayRecord data_030008B0;
extern DisplayRecord data_03000990;
extern u16 data_03000942[];
extern u8 data_06007000[];
extern u8 data_06006000[];
extern u8 data_06008000[];
extern u8 data_06005800[];
extern u8 data_06005000[];
extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);

/* 08022874..0802292C: 184 bytes, 69 instructions, including literal pools. */
void func_08022874(void)
{
    data_03000E60.control = &data_03000942[0];
    data_03000E60.horizontal_offset = &data_03000942[4];
    data_03000E60.vertical_offset = &data_03000942[5];
    data_03000E60.width = 64;
    data_03000E60.height = 32;
    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = data_06007000;

    data_03000E80.control = &data_03000942[1];
    data_03000E80.horizontal_offset = &data_03000942[6];
    data_03000E80.vertical_offset = &data_03000942[7];
    data_03000E80.width = 64;
    data_03000E80.height = 32;
    data_03000E80.tiles = (u8 *)0x06000000;
    data_03000E80.destination = data_06006000;

    func_0801E458(2, 0, 0, 0, 0, data_06008000, data_06005800);
    func_0801E458(3, 0, 0, 0, 0, data_06008000, data_06005000);

    data_030008B0.control = &data_03000942[2];
    data_030008B0.horizontal_offset = &data_03000942[8];
    data_030008B0.vertical_offset = &data_03000942[9];

    data_03000990.control = &data_03000942[3];
    data_03000990.horizontal_offset = &data_03000942[10];
    data_03000990.vertical_offset = &data_03000942[11];
}
