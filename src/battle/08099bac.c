/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct BattleActor { u8 *unit; u8 unknown_04[124]; const u8 *owner; };
typedef char ActorOwnerOffset[(u32)&((struct BattleActor *)0)->owner == 128 ? 1 : -1];
extern void ResetBattleUnitTransientState(u8 *);
extern void SetUnitStateEABit3(u8 *, u8);
extern void SetUnitStateEDBit3(u8 *, u8);
extern u8 *SelectLowestEligibleBattleNode(const u8 *, u8 **) __asm__("BattleRecordReplacement_08099494");
extern struct BattleActor *SelectLowestMatchingEDNode(const u8 *, const u8 *);
__asm__(".global SelectLowestMatchingEDNode\n.thumb_set SelectLowestMatchingEDNode, 0x080970e9");


void ResetBattleActorAndLinkedStateBits(struct BattleActor *actor);
void ResetBattleActorAndLinkedStateBits(struct BattleActor *actor)
{
    const u8 *owner;
    struct BattleActor *selected;

    ResetBattleUnitTransientState(actor->unit);
    owner = actor->owner;
    while ((selected = (struct BattleActor *)SelectLowestEligibleBattleNode(owner, &actor->unit)) != 0)
        SetUnitStateEABit3(selected->unit, 0);
    owner = actor->owner;
    while ((selected = SelectLowestMatchingEDNode(owner, actor->unit)) != 0)
        SetUnitStateEDBit3(selected->unit, 0);
}
