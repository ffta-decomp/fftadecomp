typedef unsigned char u8;
typedef signed int s32;
/* The action-selection caller separately narrows the -1 sentinel to255. */
s32 GetActionSelectionCodeOrdinal(u8 code) asm("CoreConsumer_000C9134");
s32 GetActionSelectionCodeOrdinal(u8 code)
{
    switch (code) {
    case 44:
        return 0;
    case 45:
        return 1;
    case 46:
        return 2;
    case 47:
        return 3;
    case 48:
        return 4;
    case 49:
        return 5;
    case 50:
        return 6;
    case 51:
        return 7;
    case 52:
        return 8;
    case 53:
        return 9;
    case 54:
        return 10;
    case 55:
        return 11;
    case 56:
        return 12;
    case 57:
        return 13;
    case 62:
        return 14;
    case 63:
        return 15;
    case 64:
        return 16;
    case 65:
        return 17;
    case 66:
        return 18;
    case 67:
        return 19;
    default:
        return -1;
    }
}
