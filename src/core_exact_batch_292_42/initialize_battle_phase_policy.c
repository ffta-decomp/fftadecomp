#ifndef BATTLE_PHASE_INITIALIZATION_INTERFACES_H
#define BATTLE_PHASE_INITIALIZATION_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleRegistry;
struct BattleRouteRecord;
struct BattlePhaseInitialState {
    struct BattleRegistry *registry;
    u8 unknown04[64];
    struct BattleRouteRecord *route;
    u8 unknown48[128];
    u8 pending;
    u8 unknownc9[7];
    u32 policy_flags;
    u8 unknownd4[8];
    u16 selector;
    u8 unknownde[218];
};
typedef void (*ClearBytesFunction)(void *,u32);
extern struct BattlePhaseInitialState gBattlePhaseInitialState;
extern ClearBytesFunction const gBattlePhaseClear;
extern struct BattleRouteRecord *CreateBattleRouteRecord(void);
extern void SetBattleRegistryFlag8(struct BattleRegistry *,u8 enabled);
extern u8 ReadGameFlag(u16 flag);
#define FIELD_OFFSET(T,M) ((u32)&((T *)0)->M)
typedef char PhaseSize[(sizeof(struct BattlePhaseInitialState)==440)?1:-1];
typedef char PhaseRoute[(FIELD_OFFSET(struct BattlePhaseInitialState,route)==68)?1:-1];
typedef char PhasePending[(FIELD_OFFSET(struct BattlePhaseInitialState,pending)==200)?1:-1];
typedef char PhaseFlags[(FIELD_OFFSET(struct BattlePhaseInitialState,policy_flags)==208)?1:-1];
typedef char PhaseSelector[(FIELD_OFFSET(struct BattlePhaseInitialState,selector)==220)?1:-1];
__asm__(
".global gBattlePhaseInitialState\n.set gBattlePhaseInitialState,0x0200F4E8\n"
".global gBattlePhaseClear\n.set gBattlePhaseClear,0x0836D4B8\n"
".global CreateBattleRouteRecord\n.thumb_set CreateBattleRouteRecord,0x0809D429\n"
".global SetBattleRegistryFlag8\n.thumb_set SetBattleRegistryFlag8,0x0809A5C1\n"
".global ReadGameFlag\n.thumb_set ReadGameFlag,0x080C95A9\n");
#endif


/* Numeric policy/selector labels stay neutral. Existing route allocation,
 * clear and registry implementations retain their complete original effects. */
struct BattlePhaseInitialState *InitializeBattlePhasePolicy(struct BattleRegistry *registry)
{
    register struct BattleRegistry *initial_registry asm("r4") = registry;
    register struct BattlePhaseInitialState *phase asm("r5");
    asm("" : "+r"(initial_registry));
    phase = &gBattlePhaseInitialState;
    asm("" : "+r"(phase));
    gBattlePhaseClear(phase, sizeof(*phase));
    phase->route = CreateBattleRouteRecord();
    phase->registry = initial_registry;
    {
        register u16 *selector asm("r1") = &phase->selector;
        register u32 inactive asm("r2");
        register u8 *pending asm("r0");
        asm("" : "+r"(selector));
        inactive = 0;
        asm("" : "+r"(inactive));
        *selector = 8;
        pending = &phase->pending;
        asm("" : "+r"(pending));
        *pending = inactive;
    }
    SetBattleRegistryFlag8(initial_registry, 1);
    if ((u8)ReadGameFlag(13) != 0) {
        register u32 *policy asm("r0") = &phase->policy_flags;
        asm("" : "+r"(policy));
        *policy |= 0x800;
    }
    return phase;
}
