/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08004B9C.c
 * Original SHA-256: 57819bd9820157fc2a2570d5066b2e86b364fed955708fa756246d6d2604882b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u16 control;
    u8 unknown_02[0x0A];
    u16 mode;
} SerialRegisters;

typedef struct {
    u8 bytes[0x18];
} SerialBlock;

typedef struct {
    SerialBlock first;
    SerialBlock second;
    SerialBlock third;
} SerialEntry;

typedef struct {
    u8 unknown_00[9];
    u8 field_09;
    u8 selected;
    u8 unknown_0B[9];
    s32 field_14;
    u8 unknown_18[0x10];
    SerialBlock *scratch_first;
    SerialBlock *scratch_second;
    SerialBlock *first[4];
    SerialBlock *second[4];
    SerialBlock *third[4];
    SerialBlock scratch_60;
    SerialBlock scratch_78;
    SerialEntry entries[2];
    u8 unknown_120[4];
    u8 ready;
} SerialState;

extern u16 data_03000E50;
extern u16 data_04000128;
extern u16 data_04000134;
extern SerialState data_030028A0;
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete owner: 0x08004B9C..0x08004C40, 164 bytes. */
void func_08004B9C(void)
{
    u32 fill;
    s32 i;

    data_03000E50 &= 0xFF7F;
    *(u16 *)0x04000134 = 0;
    *(u16 *)0x04000128 = 0x6033;
    fill = 0;
    func_0814186C(&fill, &data_030028A0, 0x05000056);
    data_030028A0.selected = 0xFF;
    data_030028A0.field_14 = -1;
    data_030028A0.scratch_first = &data_030028A0.scratch_60;
    data_030028A0.scratch_second = &data_030028A0.scratch_78;
    for (i = 0; i <= 1; i++)
    {
        u32 offset = i * sizeof(SerialEntry);
        data_030028A0.first[i] = (SerialBlock *)((u8 *)&data_030028A0.entries[0].first + offset);
        data_030028A0.second[i] = (SerialBlock *)((u8 *)&data_030028A0.entries[0].second + offset);
        data_030028A0.third[i] = &data_030028A0.entries[i].third;
    }
    data_030028A0.field_09 = 0;
    data_030028A0.ready = 1;
}
