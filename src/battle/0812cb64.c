/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct UnitState;
extern u8 ReadUnitStateEABit5(const struct UnitState *unit);
asm(".global ReadUnitStateEABit5\n.thumb_set ReadUnitStateEABit5,0x080cdaad");


/* Selector and action names remain neutral pending content-table naming. */
u8 IsUnitActionAllowedForSelector(const struct UnitState *unit, u16 selector, u16 action)
{
    switch (selector) {
    case 41:
        if (action == 12)
            return 0;
        break;
    case 42:
        if (action == 19)
            return 0;
        if (action == 28 && ReadUnitStateEABit5(unit))
            return 0;
        break;
    case 43:
        if (action == 51)
            return 0;
        if (action == 28 && !ReadUnitStateEABit5(unit))
            return 0;
        break;
    case 44:
        if (action == 80)
            return 0;
        break;
    case 45:
        if (action == 22)
            return 0;
        break;
    case 46:
        if (action == 24)
            return 0;
        break;
    case 47:
        if (action == 27)
            return 0;
        break;
    case 48:
        if (action == 35)
            return 0;
        break;
    case 49:
        if (action == 41)
            return 0;
        break;
    case 50:
        if (action == 42)
            return 0;
        break;
    case 51:
        if (action == 45)
            return 0;
        break;
    case 52:
        if (action == 46)
            return 0;
        break;
    case 53:
        if (action == 50)
            return 0;
        break;
    case 54:
        if (action == 56)
            return 0;
        break;
    case 55:
        if (action == 61)
            return 0;
        break;
    case 56:
        switch (action) {
        case 12:
        case 19:
        case 22:
        case 24:
        case 27:
        case 28:
        case 30:
        case 35:
        case 41:
        case 42:
        case 43:
        case 45:
        case 46:
        case 50:
        case 51:
        case 56:
        case 61:
        case 63:
        case 71:
        case 80:
            return 0;
        }
        break;
    case 57:
        switch (action) {
        case 19:
        case 27:
        case 41:
        case 45:
        case 46:
        case 50:
        case 80:
            return 0;
        }
        break;
    case 58:
        switch (action) {
        case 12:
        case 22:
        case 24:
        case 35:
        case 42:
        case 51:
        case 56:
        case 61:
        case 63:
            return 0;
        case 28:
            if (!ReadUnitStateEABit5(unit))
                return 0;
            break;
        }
        break;
    case 59:
        switch (action) {
        case 12:
        case 35:
        case 41:
        case 46:
        case 56:
        case 61:
            return 0;
        }
        break;
    }
    return 1;
}
