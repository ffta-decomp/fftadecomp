#include "ffta/unsigned_types.h"
void SceneTaskDependency_00017FB0(u8 *object, u32 input_row)
{
    u32 row = (u8)input_row;
    object[17] = row;
    *(u16 *)(object + 14) = row << 4;
}
