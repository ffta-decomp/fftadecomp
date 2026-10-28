/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801446C.c
 * Original SHA-256: 9285aeb83e63b7871704a5b3375f7f01a87a1d9bca930202e584c79d9e651a15
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_08014778(const u8 *field);
extern u16 func_08013BC0(u16 value, u8 bits);

/* Complete [0x0801446C, 0x080144F2): 134 bytes, 63 instructions. */
u16 func_0801446C(const u8 *data, u16 *total)
{
    u8 kind = data[2] & 0xF0;
    const u8 *cursor = data + 3;
    u16 first = func_08014778(cursor);
    u16 second;

    while (*cursor++ != 0)
        ;
    second = func_08014778(cursor);
    while (*cursor++ != 0)
        ;

    if (kind == 0x10) {
        first = func_08013BC0(first, 8);
        second = func_08013BC0(second, 8);
        if (total != 0)
            *total += first + second + 0x30;
    }
    return (u16)(cursor - data);
}
