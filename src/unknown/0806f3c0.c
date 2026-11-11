#include "ffta/unsigned_types.h"
void SetNativeShopBackdropParameter02(u8 *,u32) __asm__("SceneTaskDependency_0006F3C0");
void SetNativeShopBackdropParameter02(u8 *object,u32 raw_value)
{
    object[2] = raw_value;
}
