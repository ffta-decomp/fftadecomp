/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C6A0.c
 * Original SHA-256: ac6805b1d7225caa529be1e42943eadcb1035fabdc7a627f0e6274a128ef9f9f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804C6A0..0x0804C6E4: 68 bytes. */
typedef struct {
    u32 unknown_00;
    u32 value;
    u8 unknown_08[4];
    u8 type;
    u8 active;
    u8 unknown_0E[2];
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
    u8 unknown_14[8];
} Entry0804C6A0;

extern void func_0804C668(Entry0804C6A0 *entries, u16 index, u32 value,
                         u8 first, u8 second, u8 third, u8 fourth);

void func_0804C6A0(Entry0804C6A0 *entries, u16 index, u32 value,
                   u8 first, u8 second, u8 third, u8 fourth)
{
    func_0804C668(entries, index, value, first, second, third, fourth);
    entries[index].type = 4;
}
