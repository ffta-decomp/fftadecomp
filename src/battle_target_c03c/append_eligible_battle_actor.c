/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct Actor { void *unit; u8 unknown4[4]; s16 x8; u8 unknown10[2]; s16 y12; u8 unknown14[34]; u32 flags48; } Actor;
typedef struct ActorSelection { Actor *excluded; Actor *target; Actor **output; u8 count; u8 mode; } ActorSelection;
#define OFF(T,F) ((u32)&(((T *)0)->F))
typedef char actor_flags_offset[OFF(Actor,flags48)==48?1:-1];
typedef char selection_count_offset[OFF(ActorSelection,count)==12?1:-1];
extern u8 CanBattleUnitTakeTurn(const void *);
extern u8 UnitField03InRange6To18(const void *);
extern s32 ReadUnitEffectOutput(void *,u16 *);
extern u32 TestUnitCoordinates(void *,u8,u8,u8,u8,u16,u8);
extern s32 ReadUnitEffectValue(void *,void *,u8);
extern u32 TestEffectChance(u16);
__asm__(".global ReadUnitEffectOutput\n.thumb_set ReadUnitEffectOutput,0x0812f0d9");
__asm__(".global TestUnitCoordinates\n.thumb_set TestUnitCoordinates,0x0812e1a9");
__asm__(".global ReadUnitEffectValue\n.thumb_set ReadUnitEffectValue,0x0812e131");
__asm__(".global TestEffectChance\n.thumb_set TestEffectChance,0x0812f1dd");
__asm__(".global UnitField03InRange6To18\n.thumb_set UnitField03InRange6To18,0x080c8385");

u32 AppendEligibleBattleActor(Actor *,ActorSelection *);
u32 AppendEligibleBattleActor(Actor *actor,ActorSelection *selection)
{
    u16 effect;
    if(actor==selection->excluded || actor==selection->target) return 1;
    if((u8)CanBattleUnitTakeTurn(actor->unit)==0) return 1;
    if((u8)UnitField03InRange6To18(actor->unit)!=0) return 1;
    if(actor->flags48&0x8000) return 1;
    if(ReadUnitEffectOutput(actor->unit,&effect)<=0) effect=0;
    if(!TestUnitCoordinates(actor->unit,(u8)(actor->x8>>5),(u8)(actor->y12>>5),
                           (u8)(selection->target->x8>>5),(u8)(selection->target->y12>>5),effect,8)) return 1;
    if(selection->mode==1) {
        if((u8)TestEffectChance((u16)(ReadUnitEffectValue(actor->unit,selection->target->unit,0)+10))==0) return 1;
    }
    selection->output[selection->count]=actor;
    ++selection->count;
    return 1;
}
