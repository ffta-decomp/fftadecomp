/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0808136C.c
 * Original SHA-256: 5c266f89a34bf7d959268debd4525bfcc53feb5aa407818501880d21a4e93d23
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[0x22];
} Renderer;

typedef struct {
    u8 unknown_00[0x0C];
    u8 first_width;
    u8 first_height;
    u8 unknown_0E[2];
    u16 *first_destination;
    u16 *first_source;
    u8 unknown_18[0x0C];
    u8 second_width;
    u8 second_height;
    u8 unknown_26[2];
    u16 *second_destination;
    u16 *second_source;
    u16 renderer;
    u8 mode;
    u8 unknown_33[5];
    u16 field_38;
    u8 unknown_3A[4];
    u16 field_3E;
    u8 unknown_40[8];
    void *resource;
    u8 unknown_4C[0x80];
} TransferSlot;

typedef struct {
    u8 unknown_0000[0x2C88];
    TransferSlot slots[1];
} TransferState;

extern TransferState *data_03002818;
extern Renderer data_030009E0[];
extern u16 data_06008000[];

void func_0808136C(u32 slot, void *resource, u32 renderer, u32 column,
                  u32 row, u8 mode)
{
    data_03002818->slots[slot].first_width = data_030009E0[renderer].width;
    data_03002818->slots[slot].first_height = data_030009E0[renderer].height;
    data_03002818->slots[slot].first_destination = data_06008000;
    data_03002818->slots[slot].first_source =
        data_030009E0[renderer].second_plane + data_030009E0[renderer].width * row + column;
    data_03002818->slots[slot].second_width = data_030009E0[renderer].width;
    data_03002818->slots[slot].second_height = data_030009E0[renderer].height;
    data_03002818->slots[slot].second_destination = data_06008000;
    data_03002818->slots[slot].second_source =
        data_030009E0[renderer].first_plane + data_030009E0[renderer].width * row + column;
    data_03002818->slots[slot].renderer = renderer;
    data_03002818->slots[slot].field_38 = 0;
    data_03002818->slots[slot].field_3E = 0;
    data_03002818->slots[slot].mode = mode;
    data_03002818->slots[slot].resource = resource;
}
