/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef signed int s32;
struct UnitPosition { u8 prefix[246]; s8 x; s8 y; s8 z; };
extern const u8 gActionList49[];
extern const u8 gActionList65[];
extern u8 MatchTargetList(const struct UnitPosition *target, const u8 *list, s32 count);
extern s32 CheckActionPositions(const struct UnitPosition *actor, const struct UnitPosition *target, s32 actor_x, s32 actor_y, s32 target_x, s32 target_y, s32 target_z, s32 action_id);
extern u8 ReadTargetKind(const struct UnitPosition *target);
extern s32 CoreContinuation_0012C8DC(const struct UnitPosition *actor, const struct UnitPosition *target, u8 mode, s32 value);

asm(".global gActionList49\n.set gActionList49,0x083a8472\n.global gActionList65\n.set gActionList65,0x083a844c\n.global MatchTargetList\n.thumb_set MatchTargetList,0x0812d425\n.global CheckActionPositions\n.thumb_set CheckActionPositions,0x0812d1dd\n.global ReadTargetKind\n.thumb_set ReadTargetKind,0x080cd50d\n.global CoreContinuation_0012C8DC\n.thumb_set CoreContinuation_0012C8DC,0x0812c8dd");
s32 CalculateEquipmentTargetRule(const struct UnitPosition *actor, const struct UnitPosition *target, s32 action_id)
{
    s32 allowed;
    s32 score;
    switch (action_id) {
    case 49:
        if (!MatchTargetList(target, gActionList49, 3))
            return 0;
        break;
    case 65:
    case 66:
        if (!MatchTargetList(target, gActionList65, 19))
            return 0;
        break;
    }
    allowed = CheckActionPositions(actor, target, actor->x, actor->y, target->x, target->y, target->z, action_id);
    if (ReadTargetKind(target) == 9 || !allowed)
        return 0;
    score = CoreContinuation_0012C8DC(actor, target, 2, 0);
    if (score <= 99)
        score >>= 1;
    return score;
}
