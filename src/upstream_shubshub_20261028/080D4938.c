/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D4938.c
 * Original SHA-256: da000ff8e279843166943ec4256aa32f9101ebe66e7fe2a8fbe712eda61250be
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D4938..0x080D4968: 48 bytes. */
extern void func_08005B58(u32 handle);

void func_080D4938(u32 *handles, u16 count)
{
    u16 i;

    for (i = 0; i < count; i++) {
        if (handles[i] != 0) {
            func_08005B58(handles[i]);
            handles[i] = 0;
        }
    }
}
