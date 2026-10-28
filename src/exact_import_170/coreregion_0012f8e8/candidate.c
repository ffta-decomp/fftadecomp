#include "interfaces.h"

/* Remap the signed response byte before the caller's amount calculation.
 * The native export and complete original ABI remain unchanged. */
u32 RemapBattleResponseCode(u32 response) __asm__("CoreRegion_0012F8E8");
u32 RemapBattleResponseCode(u32 response)
{
    switch ((s8)response) {
    case 3:
        return 2;
    case 2:
        return 4;
    case 4:
        return 1;
    default:
        return 0;
    }
}
