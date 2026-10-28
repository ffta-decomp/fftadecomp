/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08016268.c
 * Original SHA-256: 406cb28e7a789921d61a811e5b597e7fdb67ab6391b3e54e5306c5047d0861b7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08016268..0x08016344: 220 bytes. */
extern void func_080165C4(void *, u8, u8, u16, u8, u16, u16, u8);
extern void func_08016800(void *, u8, u8, u16, u8, u16, u16, u8);
extern void func_0801692C(void *, u8, u8, u16, u8, u16, u16, u8);
extern void func_08016344(void *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(void *, u8, u8, u16, u8, u16, u8);

void func_08016268(void *primary, void *secondary, u8 first, u8 second,
                  u16 flags, u8 mode, u16 third, u16 fourth, u8 fifth)
{
    if (flags & 0x20) {
        func_080165C4(secondary, first, second, flags, mode, third, fourth, fifth);
    } else if (flags & 0x800) {
        func_08016800(secondary, first, second, flags, mode, third, fourth, fifth);
    } else if (flags & 0x400) {
        func_0801692C(secondary, first, second, flags, mode, third, fourth, fifth);
    } else {
        func_08016344(primary, first, second, flags, mode, third, 12);
        func_08016560(secondary, first, second, flags, mode, fourth, fifth);
    }
}
