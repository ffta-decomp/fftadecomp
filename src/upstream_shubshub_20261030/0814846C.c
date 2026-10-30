/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0814846C.c
 * Original SHA-256: 2d9ade82c6130cfba54d3c89712c698d00a5f3eaecac506e0ecb7cf94504d19f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct EffectNode0814846C EffectNode0814846C;
struct EffectNode0814846C {
    u8 unknown_00[0x28];
    EffectNode0814846C *next;
};

typedef struct {
    void *allocator;
    EffectNode0814846C *head;
} EffectManager0814846C;

extern EffectManager0814846C data_03003C60;

/* Complete [0x0814846C, 0x08148498): 44 bytes, 19 instructions. */
u32 func_0814846C(const EffectNode0814846C *target)
{
    EffectNode0814846C *node;

    if (target == 0)
        return 0;

    for (node = data_03003C60.head; node != 0; node = node->next) {
        if (target == node)
            return 1;
    }
    return 0;
}
