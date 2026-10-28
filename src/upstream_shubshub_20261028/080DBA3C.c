/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DBA3C.c
 * Original SHA-256: 714a521aaf9a434009e8e408af66f308a6029fe9c42ddab1b6af061ecbe7ac28
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DBA3C..0x080DBA50: 20 bytes / 9 instructions. */
extern u32 func_08005BB0(const void *object);

u8 func_080DBA3C(const void *object)
{
    if (func_08005BB0(object) != 0)
        return 1;
    return 0;
}
