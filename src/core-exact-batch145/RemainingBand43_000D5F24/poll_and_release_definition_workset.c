#include "../../../src/task_tree_core.h"
extern u32 IsDefinitionResourceComplete(void *);
extern void RemoveDefinitionResource(void *);
u32 PollAndReleaseDefinitionWorkset(void **resources,u16 count)
{
    u32 all_complete = 1;
    u16 index = 0;
    if (index < count) {
        do {
            void **cell = (void **)((u32)index * sizeof(*resources) + (u32)resources);
            if (*cell != 0) {
                if ((u8)IsDefinitionResourceComplete(*cell) != 0) {
                    /* Reload after the query: it may change the referenced cell. */
                    RemoveDefinitionResource(*cell);
                    *cell = 0;
                } else {
                    all_complete = 0;
                }
            }
            index++;
        } while (index < count);
    }
    return all_complete;
}
asm(".global IsDefinitionResourceComplete\n.thumb_set IsDefinitionResourceComplete,0x08010ff1\n"
    ".global RemoveDefinitionResource\n.thumb_set RemoveDefinitionResource,0x08011429\n");
