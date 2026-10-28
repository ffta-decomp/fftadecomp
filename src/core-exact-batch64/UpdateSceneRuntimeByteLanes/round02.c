#include "scene_context_abi.h"


void UpdateSceneRuntimeByteLanes(u32 value, u32 byte_mask_argument)
{
    u8 byte_mask = (u8)byte_mask_argument;
    u32 mask = 0xffu;
    s32 lane;
    for (lane = 0; lane < 4; ++lane, mask <<= 8) {
        if ((byte_mask & (1 << lane)) != 0) {
            /* The ROM reloads the global base for every selected lane. */
            volatile u32 *word = (volatile u32 *)
                scene_root_byte(SCENE_RUNTIME_WORD_OFFSET);
            u32 previous = *word;
            *word = (previous & ~mask) | (value & mask);
        }
    }
}
