typedef unsigned char u8;
typedef unsigned short u16;
struct AbilityDescriptor { u8 bytes[16]; };
struct BattleAbilityState {
    u8 unknown[0x3c33];
    u8 count;
    u16 abilityIds[256];
};
extern struct BattleAbilityState gBattleState;
extern struct AbilityDescriptor gAbilityDescriptors[];
extern int CheckUnitAbility(void *unit, int mode, u16 value, u8 option,
    u8 enabled, u16 extra, int zero, struct AbilityDescriptor *descriptor);
asm(".global gBattleState\n.set gBattleState,0x02000000\n.global gAbilityDescriptors\n.set gAbilityDescriptors,0x08528f34\n.global CheckUnitAbility\n.thumb_set CheckUnitAbility,0x081343c9");
int CoreFrontier_00135624(void *unit)
{
    u8 anyEligible = 0;
    int abilityIndex = 0;
    for (; abilityIndex < gBattleState.count; abilityIndex++) {
        anyEligible |= CheckUnitAbility(unit, 0, 0, 0, 1, 0, 0,
            &gAbilityDescriptors[gBattleState.abilityIds[abilityIndex]]);
    }
    return anyEligible;
}
