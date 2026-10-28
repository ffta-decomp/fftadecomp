/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0812B44C.c
 * Original SHA-256: d42532ad42248a15596ae300a8f3be69be1ab15c2acee618613d3ad28b44e97d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TransferRecord TransferRecord;
extern void func_08000ADC(TransferRecord *entry, const void *source,
                         void *destination, u16 words);

/* Complete [0x0812B44C, 0x0812B468): 28 bytes, 13 instructions. */
void func_0812B44C(TransferRecord *entry, const u8 *source,
                   void *destination, u8 index)
{
    func_08000ADC(entry, source + index * 0x2100, destination, 0x840);
}
