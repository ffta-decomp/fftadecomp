/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D996C.c
 * Original SHA-256: dd0df9cdf3bc63e87adb9ab2f3264ffe7fffdd810147102688841b0a406de547
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D996C..0x080D997C: 16 bytes. */
typedef struct {
    u8 unknown_00[4];
    void *resource;
} ResourceObject;

extern ResourceObject *func_08005BFC(int index);
extern u8 *func_0800C614(void *resource);

u8 *func_080D996C(int index)
{
    return func_0800C614(func_08005BFC(index)->resource);
}
