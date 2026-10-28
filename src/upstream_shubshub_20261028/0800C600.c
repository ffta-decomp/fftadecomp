/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C600.c
 * Original SHA-256: 22499f4fe4d9f0831ea1e932523bdd86b432c860a3d459e65042b3c6242fda3b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 selector;
    u8 unknown_10[8];
    u32 primary;
    u32 fallback;
} Object0800C600;

/* 0x0800C600 - 20 bytes.
 * Target: 00b5011cc889002801d1c86900e0886902bc0847
 */
u32 func_0800C600(const Object0800C600 *object)
{
    if (object->selector != 0)
        return object->primary;
    return object->fallback;
}
