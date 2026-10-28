#include "interfaces.h"

/* Classify the source-proven battle override codes; retain every switch slot. */
u32 ClassifyBattleResponseOverride(u32 code) __asm__("CoreRegion_0012FC74");
u32 ClassifyBattleResponseOverride(u32 code)
{
    switch ((u16)code) {
    case 1:
    case 6:
    case 11:
    case 16:
    case 21:
    case 26:
    case 31:
    case 36:
        return 3;
    case 2:
    case 7:
    case 12:
    case 17:
    case 22:
    case 27:
    case 32:
    case 37:
        return 2;
    case 3:
    case 8:
    case 13:
    case 18:
    case 23:
    case 28:
    case 33:
    case 38:
        return 4;
    case 4:
    case 9:
    case 14:
    case 19:
    case 24:
    case 29:
    case 34:
    case 39:
        return 0;
    case 5:
    case 10:
    case 15:
    case 20:
    case 25:
    case 30:
    case 35:
    default:
        return 1;
    }
}
