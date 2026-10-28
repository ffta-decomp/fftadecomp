/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DBFFC.c
 * Original SHA-256: 349c7486cf63861702bd441619e7a8c12d10017d3a088d06a13481b804b00daf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DBFFC..0x080DC012: 22 bytes / 9 instructions. */
struct Group;

extern u32 func_080DD4B4(struct Group *group, u8 index);
extern u8 func_080DB838(u32 object);

u8 func_080DBFFC(struct Group *group, u8 index)
{
    return func_080DB838(func_080DD4B4(group, index));
}
