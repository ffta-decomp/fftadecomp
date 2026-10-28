/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813C0D8.c
 * Original SHA-256: a15babcce526c8ba100541a9de04445366242a4dd51726d732879071ffb0252f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0813C0D8, 0x0813C0EC): 20 bytes, 7 instructions. */
extern void *data_0200F3BC;
extern void func_08007170(void *owner, u8 *object);

void func_0813C0D8(u8 *object)
{
    func_08007170(data_0200F3BC, object);
}
