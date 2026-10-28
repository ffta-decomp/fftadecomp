/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9C48.c
 * Original SHA-256: 030f65cc743c2d013d3b299b321676ee522dc49aefcfd035105a7296a6651a67
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D9C48..0x080D9C56: 14 bytes, 6 instructions. */
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_080D9C48(const void *const *source, void *destination)
{
    func_0814186C(*source, destination, 0xA0);
}
