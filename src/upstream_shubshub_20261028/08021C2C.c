/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08021C2C.c
 * Original SHA-256: c48ae4b988b3d507b6ea14c6a3add2c5842cbed1c5d7983a9c6b87f2df3371c0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08021C2C..0x08021C36: 10 bytes. */
typedef struct {
    u32 flags;
} Flags08021C2C;

u32 func_08021C2C(const Flags08021C2C *record)
{
    return (record->flags >> 18) & 1;
}
