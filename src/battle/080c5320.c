/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct UnitPositionView { u8 unknown00[246]; u8 x; u8 y; };
struct BattleChoiceView { struct UnitPositionView **owner; u8 unknown04[20]; u8 x; u8 y; u8 unknown1a[2]; u8 mode; };
extern u32 RetailCall_080cdb84(const struct UnitPositionView *);
extern u32 RetailCall_080c4b20(struct BattleChoiceView *);
extern u32 RetailCall_080c50ec(struct BattleChoiceView *);
extern u32 RetailCall_080c4e78(struct BattleChoiceView *);
asm(".global RetailCall_080cdb84\n.thumb_set RetailCall_080cdb84,0x080cdb85\n.global RetailCall_080c4b20\n.thumb_set RetailCall_080c4b20,0x080c4b21\n.global RetailCall_080c50ec\n.thumb_set RetailCall_080c50ec,0x080c50ed\n.global RetailCall_080c4e78\n.thumb_set RetailCall_080c4e78,0x080c4e79");

u32 AdvanceBattleChoiceMode(struct BattleChoiceView *choice)
{
    if ((u8)RetailCall_080cdb84(*choice->owner))
        choice->mode=0;
    switch (choice->mode) {
    case 1: return (u8)RetailCall_080c4b20(choice);
    case 4: return (u8)RetailCall_080c50ec(choice);
    case 5: return (u8)RetailCall_080c4e78(choice);
    default:
        choice->x=(*choice->owner)->x;
        choice->y=(*choice->owner)->y;
        break;
    case 2:
    case 3:
        break;
    }
    return 0;
}
