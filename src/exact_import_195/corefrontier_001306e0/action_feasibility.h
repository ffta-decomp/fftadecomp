#ifndef EFFECT195_ACTION_FEASIBILITY_H
#define EFFECT195_ACTION_FEASIBILITY_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ActionSimulation {
    void *actor;
    void *target;
    void *current_target;
    u8 unknown_0c[26];
    u16 flags;
};
typedef char SimulationFlagsOffset[((u32)&((struct ActionSimulation *)0)->flags == 38) ? 1 : -1];
extern struct ActionSimulation ActionSimulation;
__asm__(".global ActionSimulation\n.set ActionSimulation,0x0200f3f0");
extern void CollectActionEquipment(void *, u16 *) __asm__("0x0812f0d8");
extern void InitializeActionSimulation(u32, u32, u32) __asm__("0x0812f2a4");
extern void SelectActionSlot(u32) __asm__("0x0812f328");
extern void SetActionTarget(void *) __asm__("0x0812f34c");
extern u32 TestActionSlot(void) __asm__("0x08130fbc");
extern void MarkActionSlot(u32) __asm__("0x0812f39c");
extern u32 ReadActionKind(void) __asm__("0x0812f358");
extern s32 EvaluateActionValue(void) __asm__("0x08131b20");
u32 TestActionSimulationFeasible(void *, void *, u32) __asm__("CoreFrontier_001306E0");
#endif
