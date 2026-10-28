/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08147288.c
 * Original SHA-256: 3f27f4e6f2293138e50c3f0ee9fe68f8e2cb07c828d1c3cdf2fa890386da98b8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct EffectNode EffectNode;
struct EffectNode {
    u16 type;
    u16 flags;
    u16 handler;
    u8 unknown_06[0x1E];
    EffectNode *previous;
    EffectNode *next;
};

typedef struct {
    void *allocator;
    EffectNode *head;
} EffectManager;

extern EffectManager data_03003C60;
extern u8 data_03005668;
extern void (*const data_089A5CF8[])(EffectNode *node);
extern EffectNode *func_08148738(void *handle);
extern void func_08007170(void *owner, u8 *allocation);

/* 0x08147288: 148 bytes; dispatch effects and remove flagged inactive nodes. */
void func_08147288(void)
{
    EffectNode *current;

    if (data_03005668)
        return;

    data_03005668 = 1;
    for (current = data_03003C60.head; current; current = current->next) {
        if (current->type == 1) {
            data_089A5CF8[current->handler](current);
        } else if (current->type == 0) {
          if (current->flags & 8) {
            EffectNode *node = func_08148738(current);

            if (node) {
                EffectNode *previous = node->previous;
                EffectNode *next = node->next;

                if (previous) {
                    previous->next = next;
                    next->previous = previous;
                } else {
                    data_03003C60.head = next;
                    next->previous = previous;
                }
                func_08007170(data_03003C60.allocator, (u8 *)node);
            }
          }
        }
    }
    data_03005668 = 0;
}
