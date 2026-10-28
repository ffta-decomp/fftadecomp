/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808537C.c
 * Original SHA-256: 69876b19484c83ee9869638d6a9ebc9545939cc164a5446197375722ef79fe0c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x4c];
    u8 first[0x14];
    u8 second[0x14];
} Object0808537C;

extern void func_080812E8(void *context, void *entry, s32 enabled);

/* 0x0808537C..0x080853A0: 36 bytes, 16 instructions. */
void func_0808537C(void *context, Object0808537C *object, s32 enabled)
{
    func_080812E8(context, object->first, enabled);
    if (enabled)
        func_080812E8(context, object->second, enabled);
}
