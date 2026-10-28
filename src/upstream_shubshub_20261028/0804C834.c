/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C834.c
 * Original SHA-256: 0b6815a1f0985d0a2e6834a649ea365eb7ca6831fd8fd27deb6811342429425b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0804C834, 0x0804C858), 36 bytes. */
typedef struct {
    u8 unknown_00[0x0D];
    u8 active;
    u8 unknown_0E[0x0E];
} Entry0804C7A0;

extern void func_0804C7A0(Entry0804C7A0 *entries, u16 index);

void func_0804C834(Entry0804C7A0 *entries, s32 count)
{
    u16 index;

    for (index = 0; index < count; index++)
        func_0804C7A0(entries, index);
}
