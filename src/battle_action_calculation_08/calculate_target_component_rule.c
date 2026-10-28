/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
struct UnitView { u8 prefix[246]; s8 components[3]; };
extern int CoreRegion_0012C7F4(struct UnitView *source, struct UnitView *target, u16 ability, int sourceFirst, int sourceSecond, int targetFirst, int targetSecond, int targetThird, u8 mode, u8 option);
extern u8 UnitStateEAHasBit1(struct UnitView *unit);
asm(".global CoreRegion_0012C7F4\n.thumb_set CoreRegion_0012C7F4,0x0812c7f5\n");

/* Components are signed bytes; their spatial interpretation remains tentative. */
int CalculateTargetComponentRule(struct UnitView *source, struct UnitView *target, u16 ability, u8 mode, u8 option)
{
    int sourceFirst = source->components[0];
    int result = CoreRegion_0012C7F4(source, target, ability, sourceFirst,
        source->components[1], target->components[0], target->components[1],
        target->components[2], mode, option);
    if (result != 0 && UnitStateEAHasBit1(target))
        result = 100;
    return result;
}
