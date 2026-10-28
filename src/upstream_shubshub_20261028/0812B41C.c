/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812B41C.c
 * Original SHA-256: 6caa760ff8625c8642a474be0b4cd150ea4a84284f0cb1c1eb1b0fecd09e6d11
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TransferRecord TransferRecord;

extern u8 data_02003CB0[];
extern const u8 data_083C5454[];
extern void func_08005318(const void *table, void *destination,
                         u32 index, u32 flag);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                         void *destination, u16 words);

/* Complete [0x0812B41C, 0x0812B44C): 48 bytes, 18 instructions. */
void func_0812B41C(TransferRecord *entry, void *destination, u8 index)
{
    u8 *buffer = data_02003CB0;

    func_08005318(data_083C5454, buffer, index, 1);
    func_08000ADC(entry, buffer, destination, 0xC0);
}
