/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitChoiceView { u8 unknown00[6]; u8 unit_id; u8 unknown07[53]; u8 choice; };
struct ChoiceRecord { u32 unknown00; u16 content_id; u8 kind; };
struct ContentRule { u8 unknown00; u8 category:5; u8 upper:3; u8 unknown02[2]; } __attribute__((packed));
extern struct ChoiceRecord *RetailCall_080cd480(u8,u8);
asm(".global RetailCall_080cd480
.thumb_set RetailCall_080cd480,0x080cd481");

u32 ReadChoiceCategoryValue(const struct UnitChoiceView *unit)
{
    struct ChoiceRecord *choice=RetailCall_080cd480(unit->unit_id,unit->choice);
    if (choice->kind == 5) {
        const struct ContentRule *rules=(const struct ContentRule *)0x0852736c;
        switch (rules[choice->content_id].category) {
        case 0: return 5;
        case 1: return 8;
        case 2: return 10;
        case 3: return 12;
        case 4: return 15;
        }
    }
    return 0;
}
