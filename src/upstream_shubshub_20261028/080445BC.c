/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080445BC.c
 * Original SHA-256: 913dcb022b274155c439a92df78b77878cff4b8f88a77059d299bb1f073cb807
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080445BC, 0x080445DA), 30 bytes. */
struct EntrySpecification {
    u8 slot : 3;
    u8 unknown_03 : 1;
    u8 mode : 2;
    u8 type : 4;
    u8 unknown_0a : 6;
    u8 position : 5;
    u8 unknown_15 : 2;
    u8 resource : 8;
    u8 unknown_1f : 1;
} __attribute__((packed));

extern u32 func_080445DC(struct EntrySpecification *specification, u8 slot,
                        u32 unused, u8 option);

u32 func_080445BC(struct EntrySpecification *specification, u8 option)
{
    return func_080445DC(specification, (u8)(specification->position - 1),
                          0, option);
}
