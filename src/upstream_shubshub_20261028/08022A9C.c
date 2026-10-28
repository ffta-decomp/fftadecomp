/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022A9C.c
 * Original SHA-256: d992acdf934a215bd66beaea0c7439d7275d61503087c130dde44e96b22fc77a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08022A9C, 0x08022B24), 136 bytes. */
extern u8 data_02003CB0[];
extern const u8 data_083A93AC[];
extern const u8 data_083A94CC[];
extern const u8 data_083A9CA4[];
extern u8 data_06012400[];
extern u8 data_06008000[];
extern u8 data_06008A40[];

extern void func_08005318(const void *source, void *destination,
                          u32 index, u32 flag);
extern void func_08141868(const void *source, void *destination, u32 control);
extern u8 func_080C95A8(u16 index);
extern void func_0802292C(u32 value);
extern void func_08022A04(u32 value);

void func_08022A9C(void)
{
    u8 *buffer = data_02003CB0;

    func_08005318(data_083A93AC, buffer, 0, 0);
    func_08141868(buffer, data_06012400, 0x40);
    func_08005318(data_083A94CC, buffer, 0, 0);
    func_08141868(buffer, data_06008000, 0x290);
    if (!func_080C95A8(8)) {
        func_08005318(data_083A9CA4, buffer, 0, 0);
        func_08141868(buffer, data_06008A40, 0x210);
        func_0802292C(0xff);
    } else {
        func_08022A04(0xff);
    }
}
