/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct Unit { u8 unknown00[246]; u8 x,y; };
struct Actor { struct Unit *unit; u8 unknown04[124]; void *battle; };
struct PhaseHistory { u16 phase,count; u16 entries[0]; };
struct BattleSelection {
    u32 unknown00; struct Actor *actor;
    u8 unknown08[0x54af-8]; u8 flags;
    u8 unknown54b0[0x54c8-0x54b0]; u16 property21; u8 x,y;
    u8 unknown54cc[0x54f4-0x54cc]; struct PhaseHistory progress;
};
typedef char ActorBattleOffset[(u32)&((struct Actor*)0)->battle==128?1:-1];
typedef char FlagsOffset[(u32)&((struct BattleSelection*)0)->flags==0x54af?1:-1];
typedef char PropertyOffset[(u32)&((struct BattleSelection*)0)->property21==0x54c8?1:-1];
typedef char PhaseOffset[(u32)&((struct BattleSelection*)0 )->progress.phase==0x54f4?1:-1];
typedef char HistoryOffset[(u32)&((struct BattleSelection*)0 )->progress.entries==0x54f8?1:-1];
extern void (*const ClearSelectionBytes)(void *,s32);
extern u32 ReadSaveByte(u16);
extern u32 CheckSelectionMode(struct Actor *);
extern u32 IsActorInInitialPair(struct Actor *);
extern struct Actor *FindRelatedActor(void *,struct Unit *);
extern void SelectBattleMessage(u16);
extern u32 HasSelectionAbility(const struct Unit *);
extern u32 HasUnitStateEB6(const struct Unit *);
extern u32 ReadMovementValue(const struct Unit *);
extern u32 ReadUnitField(const struct Unit *,u8);
__asm__(".global ClearSelectionBytes\n.set ClearSelectionBytes,0x0836d4b8\n.global ReadSaveByte\n.thumb_set ReadSaveByte,0x080c95a9\n.global CheckSelectionMode\n.thumb_set CheckSelectionMode,0x080c1b2d\n.global IsActorInInitialPair\n.thumb_set IsActorInInitialPair,0x0809aa11\n.global FindRelatedActor\n.thumb_set FindRelatedActor,0x080970e9\n.global SelectBattleMessage\n.thumb_set SelectBattleMessage,0x080c71b5\n.global HasSelectionAbility\n.thumb_set HasSelectionAbility,0x081341ed\n.global HasUnitStateEB6\n.thumb_set HasUnitStateEB6,0x080cdb85\n.global ReadMovementValue\n.thumb_set ReadMovementValue,0x080ca3ed\n.global ReadUnitField\n.thumb_set ReadUnitField,0x080c7ea5\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n.global __udivsi3\n.thumb_set __udivsi3,0x08142ab1");

void InitializeBattleSelection(struct BattleSelection *selection,struct Actor *actor);
void InitializeBattleSelection(struct BattleSelection *selection,struct Actor *actor)
{
    ClearSelectionBytes(selection,0x553c);
    selection->actor=actor;
    if ((u8)ReadSaveByte(13)) {
        if (!(u8)CheckSelectionMode(actor)) {
            u8 initial_pair=IsActorInInitialPair(actor);
            if (FindRelatedActor(actor->battle,actor->unit)) initial_pair=1;
            if (initial_pair) SelectBattleMessage(8);
            else SelectBattleMessage(9);
            selection->progress.phase=11;
            return;
        }
        SelectBattleMessage(9);
    }
    if ((u8)HasSelectionAbility(actor->unit)) selection->flags|=4;
    if ((u8)HasUnitStateEB6(actor->unit) || ReadMovementValue(actor->unit)/10u==0)
        selection->flags|=64;
    selection->property21=ReadUnitField(actor->unit,21);
    {
        struct Unit *unit=actor->unit;
        u16 old_count;
        struct PhaseHistory *progress;
        selection->x=unit->x;
        selection->y=unit->y;
        progress=&selection->progress;
        progress->phase=0;
        old_count=progress->count++;
        progress->entries[old_count]=0;
        progress->phase=9;
    }
}
