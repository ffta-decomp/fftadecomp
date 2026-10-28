typedef unsigned char u8;
typedef unsigned int u32;

struct BattleActionSelection {
    u8 preceding_fields[4];
    u8 selector;
};

/* The root contains a pointer, not the selector itself. Case captions remain
 * unresolved; preserve the observed game-specific action mapping. */
u32 SelectBattleStateAction_08027D10(void)
{
    u32 action = 0;
    struct BattleActionSelection *selection =
        *(struct BattleActionSelection **)0x0200f438;

    switch (selection->selector) {
    case 1:
        action = 0;
        break;
    case 4:
    case 10:
        action = 1;
        break;
    case 5:
        action = 2;
        break;
    case 6:
    case 7:
    case 8:
        action = 3;
        break;
    case 11:
        action = 4;
        break;
    case 12:
        action = 5;
        break;
    case 2:
        action = 6;
        break;
    case 3:
        action = 7;
        break;
    case 13:
        action = 8;
        break;
    case 14:
        action = 9;
        break;
    case 15:
        action = 10;
        break;
    }
    return action;
}
