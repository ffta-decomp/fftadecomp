typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
extern u8 CanTargetEvade(void *target);
extern u8 CheckTargetFacing(void *target, s8 x, s8 y);
extern u8 CheckAbilityAvoidance(void *target, u16 ability, u8 mode);
extern int ReadTargetAvoidance(void *target);
extern int ClassifyRelativeFacing(s8 sourceX, s8 sourceY, s8 targetX, s8 targetY, s8 targetHeight);
extern int ReadPairAvoidanceAdjustment(void *source, void *target);
extern int ReadSourceAbilityAdjustment(void *source);
extern int ClampAvoidance(int value);
extern s8 gFacingDivisors[];
asm(".global CanTargetEvade\n.thumb_set CanTargetEvade,0x0812c56d\n.global CheckTargetFacing\n.thumb_set CheckTargetFacing,0x0812f0e5\n.global CheckAbilityAvoidance\n.thumb_set CheckAbilityAvoidance,0x0812c5cd\n.global ReadTargetAvoidance\n.thumb_set ReadTargetAvoidance,0x0812c7b9\n.global ClassifyRelativeFacing\n.thumb_set ClassifyRelativeFacing,0x0812c701\n.global ReadPairAvoidanceAdjustment\n.thumb_set ReadPairAvoidanceAdjustment,0x0812c635\n.global ReadSourceAbilityAdjustment\n.thumb_set ReadSourceAbilityAdjustment,0x0812c611\n.global ClampAvoidance\n.thumb_set ClampAvoidance,0x0812c671\n.global gFacingDivisors\n.set gFacingDivisors,0x083a8444\n.global __divsi3\n.thumb_set __divsi3,0x081426b9");
int CoreRegion_0012C7F4(void *source, void *target, u16 ability,
    u8 sourceX, u8 sourceY, u8 targetX, u8 targetY, u8 targetHeight,
    int enableAbilityGate, u8 abilityMode)
{
    int avoidance;
    if (!CanTargetEvade(target))
        return 100;
    if (enableAbilityGate != 0 &&
        CheckTargetFacing(target, (s8)targetX, (s8)targetY) &&
        CheckAbilityAvoidance(target, ability, abilityMode))
        return 0;
    avoidance = ReadTargetAvoidance(target);
    avoidance /= gFacingDivisors[ClassifyRelativeFacing((s8)sourceX,
        (s8)sourceY, (s8)targetX, (s8)targetY, (s8)targetHeight)];
    avoidance += ReadPairAvoidanceAdjustment(source, target);
    avoidance += ReadSourceAbilityAdjustment(source);
    avoidance = ClampAvoidance(avoidance);
    return 100 - avoidance;
}
