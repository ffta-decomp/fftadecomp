/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080611D0.c
 * Original SHA-256: ec34060e5e8541f54104741ee9681186324247a86474651f15ea8b28c8971bea
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080611D0..0x080611EE: 30 bytes. */
extern void func_0802A2C0(u32 first, u32 second, u32 third, u32 fourth);
extern void func_0802A370(u32 first, u32 second, u32 third, u32 fourth);

void func_080611D0(void)
{
    func_0802A2C0(0x11, 1, 0x0D, 0x12);
    func_0802A370(0, 0, 0, 0);
}
