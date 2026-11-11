/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0804DBF8.c
 * Original SHA-256: 91f38805de052b9d2d7e8dccc21d5f9681d04d39ac52e2b0023745f67c00fdc5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 *buffer;
} GraphicsState;

extern GraphicsState data_030008B0;
extern u8 data_02003CB0[];
extern const u8 data_083A93AC[];
extern const u8 data_083A94CC[];
extern const u8 data_083AEEA4[];
extern const u8 data_083AF504[];
extern const u8 data_083B4214[];
extern const u8 data_083C5024[];
extern u8 data_06012400[];
extern u8 data_06008000[];
extern u8 data_06008A40[];
extern u8 data_06012500[];
extern u8 data_06012700[];

extern s32 func_08005318(const void *, u8 *, u16, u16);
extern u32 func_0800543C(u8 *, const u8 *);
extern void func_080CB9B0(void *, u32);
extern void func_08141868(const void *, void *, u32);
extern void func_0814186C(const void *, void *, u32);

void func_0804DBF8(void)
{
    u8 *base = data_030008B0.buffer;
    u8 *destination = base + 0x1C00;
    u8 *buffer = data_02003CB0;

    func_08005318(data_083A93AC, buffer, 0, 0);
    func_08141868(buffer, data_06012400, 0x40);
    func_08005318(data_083A94CC, buffer, 0, 0);
    func_08141868(buffer, data_06008000, 0x290);
    func_0800543C(buffer, data_083AEEA4);
    func_0814186C(buffer, data_06008A40, 0x5A0);
    func_0800543C(buffer, data_083AF504);
    func_0814186C(buffer, data_06012500, 0x100);

    func_080CB9B0(buffer, 15);
    func_0814186C(buffer, destination, 0x40);
    destination = base + 0x1C80;
    func_080CB9B0(buffer, 16);
    func_0814186C(buffer, destination, 0x40);
    destination = base + 0x1D00;
    func_080CB9B0(buffer, 17);
    func_0814186C(buffer, destination, 0x40);
    destination = base + 0x1D80;
    func_080CB9B0(buffer, 18);
    func_0814186C(buffer, destination, 0x40);
    destination = base + 0x1E00;
    func_080CB9B0(buffer, 6);
    func_0814186C(buffer, destination, 0x40);
    destination = base + 0x1E80;
    func_080CB9B0(buffer, 19);
    func_0814186C(buffer, destination, 0x40);

    destination = base + 0x1F00;
    func_0800543C(buffer, data_083B4214);
    func_08141868(buffer + 0x560, destination, 0x10);
    func_0800543C(buffer, data_083C5024);
    func_08141868(buffer + 0xA80, data_06012700, 0x20);
}
