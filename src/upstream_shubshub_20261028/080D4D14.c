/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D4D14.c
 * Original SHA-256: 5e40efea26de261f140b63cae0a34b98d4b6a8eb88754a96beb490a9fe01276d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_0800C224(void *object);
extern void func_0800C1C8(u8 mode);

void func_080D4D14(void *object, u8 mode)
{
    func_0800C224(object);
    func_0800C1C8(mode);
}
