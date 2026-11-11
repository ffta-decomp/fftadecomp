/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08057BEC.c
 * Original SHA-256: 13cdd323593c20814a28b76191b20e8fb05391eafc98ef217d840a0c7db2d678
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_0000[0x2fc2];
    u8 selection : 2;
    u8 unknown_2fc2 : 6;
} State08057BEC;

extern State08057BEC g_state_02000000;
extern u8 data_02003CB0[];
extern u8 data_0600A400[];
extern u8 data_06009800[];
extern u8 data_03003960[];
extern u8 data_06015C00[];
extern const u8 data_083AD5F8[];
extern const u8 data_083ACD68[];
extern const u8 *data_08391960[];

extern void func_080CB9B0(void *object, u32 value);
extern u8 *func_0800543C(void *destination, const void *source);
extern void func_08005318(const void *source, void *destination, u32 index, u32 flag);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_08018524(u8 *destination, u16 code, u8 variant);

/* Complete [0x08057BEC, 0x08057C88): 156 bytes, 50 instructions. */
void func_08057BEC(void)
{
    u8 *buffer = data_02003CB0;

    func_080CB9B0(buffer, 0x1e);
    func_08141868(buffer, data_0600A400, 0x20);
    func_0800543C(buffer, data_083AD5F8);
    func_0814186C(buffer + 0x860, data_06009800, 0x140);
    func_0814186C(data_08391960[g_state_02000000.selection * 2] + 0x60,
                  data_03003960, 0x10);
    func_08005318(data_083ACD68, buffer, 0, 0);
    func_0814186C(buffer, data_06015C00, 0x3c0);
    func_08018524(buffer, 0x340, 2);
}
