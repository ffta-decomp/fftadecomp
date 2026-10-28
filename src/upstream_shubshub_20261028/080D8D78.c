/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8D78.c
 * Original SHA-256: 73bd031d406a66a6cf02fc43e172fe99aa2b38eaf2309621d754b416e6f1f7ca
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern const u8 data_088EB4A4[];
extern void func_080D45D0(const void *data, u32 first, u32 second,
                         u32 third, u32 mode);

/* Complete [0x080D8D78, 0x080D8D98): 32 bytes, 12 instructions. */
void func_080D8D78(void)
{
    func_080D45D0(data_088EB4A4, 0, 0, 0, 6);
}
