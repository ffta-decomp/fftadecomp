#ifndef BATTLE_ACTION_KIND_POLICY_H
#define BATTLE_ACTION_KIND_POLICY_H

typedef unsigned char u8;
typedef unsigned int u32;

struct BattleActionRecord {
    u8 unknown_00;
    u8 type;
    u8 unknown_02;
    u8 subtype;
};
struct BattleActionContext {
    u8 unknown_00[48];
    /* Ordinary game-state pointer; entry and fallback loads remain explicit. */
    const struct BattleActionRecord *current_record;
};
extern struct BattleActionContext gBattleActionContext;
extern u32 ReadDefaultActionKind(u32 type);
__asm__(".global gBattleActionContext\n.set gBattleActionContext, 0x0200f3f0");
__asm__(".global ReadDefaultActionKind\n.thumb_set ReadDefaultActionKind, 0x08133971");

#endif


u32 ClassifyCurrentBattleAction(void) __asm__("ActionDependency_0012F358");
u32 ClassifyCurrentBattleAction(void)
{
    register struct BattleActionContext *context asm("r2") = &gBattleActionContext;
    const struct BattleActionRecord *record;
    /* Original initialized context root R2, before the entry record load. */
    asm("" : "+r"(context));
    record = context->current_record;
    if (record->type == 0x3b) {
        switch (record->subtype) {
        case 9:
            return 6;
        case 17:
            return 7;
        case 6:
            return 4;
        }
    }
    return (u8)ReadDefaultActionKind(context->current_record->type);
}
