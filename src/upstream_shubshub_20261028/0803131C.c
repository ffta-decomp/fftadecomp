/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803131C.c
 * Original SHA-256: b9d24007a8d1fe098df74b91297288d4cb2d9d867445e9c3fcf0fe76dc3ac2ef
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_02003CB0[];
extern const u8 data_083AEEA4[];
extern u8 data_06008A40[];
extern void func_0800543C(void *, const void *);
extern void func_0814186C(const void *, void *, u32);

/* 0x0803131C..0x08031348: 44 bytes, 13 instructions. */
void func_0803131C(void)
{
    u8 *buffer = data_02003CB0;

    func_0800543C(buffer, data_083AEEA4);
    func_0814186C(buffer, data_06008A40, 0x5a0);
}
