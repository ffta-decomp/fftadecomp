/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08004C40.c
 * Original SHA-256: 8d04cd1e1803fbacbb37112d598502bb7a00a3a1c8848b9a784569b644cd5dda
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[8];
    u8 field_09;
} SerialState08004C40;

typedef struct {
    u8 unknown_00[6];
    u16 interrupt_mask;
} InterruptState08004C40;

extern SerialState08004C40 data_030028A0;
extern InterruptState08004C40 data_03000EA0;
extern u16 data_03000E50;
extern u32 data_03000870;
extern u32 data_03002780;
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x08004C40, 0x08004CD4), 148 bytes:
 * 70b583b0164e0024747216480460164ad18816480840d0801549088015490880
 * 15480480d839154a101c08801448048000941449144d68462a1c3cf1f7fd0194
 * 01a812492a1c3cf1f1fd029402a8104a311c3cf1ebfd03b070bc01bc00470000
 * a02800030c010004a00e00033fff0000500e0003000200043401000433300000
 * 2a01000470080003010000058027000356000005
 */
void func_08004C40(void)
{
    u16 mask;
    u32 fill_first;
    u32 fill_second;
    u32 fill_state;

    data_030028A0.field_09 = 0;
    *(u32 *)0x0400010C = 0;
    mask = data_03000EA0.interrupt_mask & 0xFF3F;
    data_03000EA0.interrupt_mask = mask;
    data_03000E50 = mask;
    *(u16 *)0x04000200 = mask;
    *(u16 *)0x04000134 = 0;
    *(u16 *)0x04000128 = 0x3033;
    *(u16 *)0x0400012A = 0;

    fill_first = 0;
    func_0814186C(&fill_first, &data_03000870, 0x05000001);
    fill_second = 0;
    func_0814186C(&fill_second, &data_03002780, 0x05000001);
    fill_state = 0;
    func_0814186C(&fill_state, &data_030028A0, 0x05000056);
}
