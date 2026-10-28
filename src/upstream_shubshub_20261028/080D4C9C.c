/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D4C9C.c
 * Original SHA-256: 92ddc485b788f91f7c90bd83618a9229641a9d5ba6cff8c617df011d470c8b60
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void *func_0800B2A4(u8 kind, u32 first, u32 second, u32 third, u32 fourth);
extern void *func_0800B394(u32 kind, u32 first, u32 second, u32 third, u32 fourth);
extern void func_0800BEDC(void *object, u8 mode);
extern void func_0800BED8(void *object, s16 value);

void *func_080D4C9C(u8 kind, u32 first, u32 second, u8 enabled, u16 value, u8 mode)
{
    void *object;

    if (enabled)
        object = func_0800B2A4(kind, first, second, 0, 0);
    else
        object = func_0800B394(0, first, second, 0, 0);
    func_0800BEDC(object, mode);
    func_0800BED8(object, (s16)value);
    return object;
}
