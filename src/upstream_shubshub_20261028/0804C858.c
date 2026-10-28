/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C858.c
 * Original SHA-256: 6bf34183555c919109550adb88b6490b2d15044b19edf10996c6a96c4a65a919
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_02003CB0[];
extern u32 func_08005318(const u8 *source, void *destination,
                         u16 first, u16 count);
extern u16 func_080053D4(const u8 *source);
extern void func_08141868(const void *source, void *destination, u32 control);

/* Complete [0x0804C858, 0x0804C888): 48 bytes, 19 instructions. */
void func_0804C858(const u8 *source, void *destination)
{
    u8 *buffer = data_02003CB0;
    u16 count;

    func_08005318(source, buffer, 0, 0);
    count = func_080053D4(source);
    func_08141868(buffer, destination, count << 4);
}
