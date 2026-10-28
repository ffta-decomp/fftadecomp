/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148540.c
 * Original SHA-256: d5ee3ed12ac633e6a1f1105cc520ea361e472b8698c2c31a4e92499587cd25c6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct EffectNode EffectNode;
struct EffectNode {
    u8 unknown_00[0x24];
    EffectNode *previous;
    EffectNode *next;
};

typedef struct {
    void *allocator;
    EffectNode *head;
} EffectManager;

extern EffectManager data_03003C60;
extern EffectNode *func_08148738(void *handle);
extern void func_08007170(void *owner, u8 *allocation);

void func_08148540(void)
{
    EffectNode *current;

    for (current = data_03003C60.head; current; current = current->next)
    {
        EffectNode *node = func_08148738(current);
        if (node)
        {
            EffectNode *previous = node->previous;
            EffectNode *next = node->next;

            if (previous)
            {
                previous->next = next;
                next->previous = previous;
            }
            else
            {
                data_03003C60.head = next;
                next->previous = previous;
            }
            func_08007170(data_03003C60.allocator, (u8 *)node);
        }
    }
}
