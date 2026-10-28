/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08004FF4.c
 * Original SHA-256: a5194211290d16ccfe61e3f6c50deb0f5e6952b6fd6dca1ef9fb24660b06386f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08004FF4..0x08005028: 52 bytes, 20 instructions. */
extern const char data_03002892[];
extern u32 func_081444B8(const char *string);
extern s32 func_081443B0(const char *left, const char *right, u32 count);

u32 func_08004FF4(const char *string)
{
    if (func_081444B8(string) <= 1) {
        return 0;
    }
    if (func_081443B0(string, data_03002892, func_081444B8(string)) == 0) {
        return 1;
    }
    return 0;
}
