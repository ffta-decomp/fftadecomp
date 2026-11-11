#include "ffta/unsigned_types.h"
void SetNativeShopBackdropParameter04(u8 *,u32) __asm__("SceneTaskDependency_0006F3C4");
void SetNativeShopBackdropParameter04(u8 *object,u32 raw_value)
{
    *(u16 *)(object+4) = raw_value;
}
