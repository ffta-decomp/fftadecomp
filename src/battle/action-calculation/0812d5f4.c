/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed int s32;
extern s32 ReadTargetValue(const void *target);
extern s32 EvaluateTargetValue(s32 value, s32 parameter);
extern u8 CheckActorTargetValue(const void *actor, const void *target, s32 value);
extern s32 CoreContinuation_0012C8DC(const void *actor, const void *target, u8 mode, s32 parameter);
extern u8 ReadTargetKind(const void *target);
extern u8 CoreContinuation_0012D5A0(const void *actor);

asm(".global ReadTargetValue\n.thumb_set ReadTargetValue,0x80ca3ed\n.global EvaluateTargetValue\n.thumb_set EvaluateTargetValue,0x8142ab1\n.global CheckActorTargetValue\n.thumb_set CheckActorTargetValue,0x812d475\n.global CoreContinuation_0012C8DC\n.thumb_set CoreContinuation_0012C8DC,0x812c8dd\n.global ReadTargetKind\n.thumb_set ReadTargetKind,0x80cd50d\n.global CoreContinuation_0012D5A0\n.thumb_set CoreContinuation_0012D5A0,0x812d5a1");
s32 CalculateTargetStateValueRule(const void *actor, const void *target, s32 value, s32 action_id)
{
    s32 score;
    if (!EvaluateTargetValue(ReadTargetValue(target), 10) || !CheckActorTargetValue(actor, target, value))
        return 0;
    score = CoreContinuation_0012C8DC(actor, target, 2, 0);
    if (ReadTargetKind(target) == 9)
        return 0;
    if (score <= 99) {
        if (action_id == 15)
            score >>= 2;
        if (CoreContinuation_0012D5A0(actor))
            score += 20;
    }
    return score;
}
