/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D3888.c
 * Original SHA-256: 6e119f3862099bb2e797898537461264efa864a892d0b2b647ec3ef270f97c2a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D3888..0x080D38B4: 44 bytes. */
extern u32 data_0200F430;
extern u8 func_08005BB0(u32 handle);
extern void func_080058A4(u32 parent, u32 handle);

u32 func_080D3888(u32 handle)
{
    if (handle != 0 && func_08005BB0(handle)) {
        func_080058A4(data_0200F430, handle);
        return 0;
    }
    return handle;
}
