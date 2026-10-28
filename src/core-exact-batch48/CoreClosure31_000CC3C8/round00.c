#include "interfaces.h"
/* Category grouping and packed increments are observed; individual game names unknown. */
u32 ReadCategoryProgressionIncrement(u8 category, u8 row)
    asm("CoreClosure31_000CC3C8");
u32 ReadCategoryProgressionIncrement(u8 category, u8 row)
{
    switch (category) {
    case 0:
    case 1:
        return gProgressionRows[row].increment0;
    case 2:
    case 3:
    case 4:
        return gProgressionRows[row].increment1;
    case 5:
    case 6:
        return gProgressionRows[row].increment2;
    case 7:
    case 8:
    case 9:
        return gProgressionRows[row].increment3;
    case 10:
    case 11:
        return gProgressionRows[row].increment4;
    case 12:
    case 13:
        return gProgressionRows[row].increment5;
    case 14:
    case 15:
        return gProgressionRows[row].increment6;
    case 16:
    case 17:
        return gProgressionRows[row].increment7;
    case 18:
    case 19:
        return gProgressionRows[row].increment8;
    default:
        return 0;
    }
}
