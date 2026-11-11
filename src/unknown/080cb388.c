typedef unsigned char u8;
typedef unsigned short u16;

/* Map the fourteen compact extended-inventory selectors to their item IDs. */
u16 MapSpecialItemIndex(u8 index)
{
    switch (index) {
    case 1: return 362;
    case 2: return 363;
    case 3: return 364;
    case 4: return 365;
    case 5: return 366;
    case 6: return 375;
    case 7: return 369;
    case 8: return 370;
    case 9: return 371;
    case 10: return 373;
    case 11: return 372;
    case 12: return 367;
    case 13: return 374;
    case 14: return 368;
    default: return 0;
    }
}
__asm__(".align 2, 0");
