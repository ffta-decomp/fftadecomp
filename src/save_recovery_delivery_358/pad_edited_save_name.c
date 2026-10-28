#include "../task_tree_core.h"
extern u32 NameByteLength(const u8 *name);
/* Fill only the remaining cells; the caller owns the terminating cell. */
void PadEditedSaveName(u8 *name)
{
    u8 token_count = (u8)(NameByteLength(name) >> 1);
    u8 index;
    for (index = 0; index < 9 - token_count; ++index) {
        u8 *token = name + 2 * (token_count + index);
        token[0] = 0x40;
        token[1] = 0x73;
    }
}
asm(".global NameByteLength\n.thumb_set NameByteLength,0x081444b9\n");
