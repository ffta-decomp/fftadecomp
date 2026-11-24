/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08125938.c
 * Original SHA-256: 33cab8c751371eb87daa95d82fbbcac5c5287407b0847779b74d1df92061d994
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 width;
    u8 height;
    u8 *tiles;
    void *destination;
} DisplayRecord;

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

extern DisplayRecord data_03000E80;
typedef struct {
    u16 unknown_00;
    u16 field_02;
} DisplayControl;

extern DisplayControl data_03003920;
extern RequestNode data_02007EB0;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);

/* Complete target [0x08125938, 0x08125994), 92 bytes. */
void func_08125938(void)
{
    u16 fill_value;
    u16 zero;
    u16 *source;

    *data_03000E80.horizontal_offset = zero = 0;
    *data_03000E80.vertical_offset = zero;
    data_03003920.field_02 = zero;
    source = &fill_value;
    *source = 0x1111;
    func_0814186C(source, data_03000E80.tiles + 0x7FE0, 0x01000010);
    func_08000B20(&data_02007EB0, 0x63FF,
                  (u32)data_03000E80.destination, 0x400);
}
