/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808F74C.c
 * Original SHA-256: 7285ea5b629185cd15516104212d875a0703ee113dbf52059555304a45c1e7d7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0808F74C, 0x0808F770): 36 bytes, 10 instructions. */
extern const u8 data_08A38ADC[];
extern const u8 data_08A3991C[];
extern u8 data_03005F28[];
extern void func_0814186C(const void *, void *, u32);

void func_0808F74C(void)
{
    u32 size = data_08A3991C - data_08A38ADC;
    func_0814186C(data_08A38ADC, data_03005F28, (size >> 1) & 0x1fffff);
}
