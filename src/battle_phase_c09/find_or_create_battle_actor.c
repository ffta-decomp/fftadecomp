/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct UnitCoordinates { u8 bytes00[246]; u8 x; u8 y; u8 direction; } UnitCoordinates;
typedef struct Actor { UnitCoordinates *unit; u8 unknown4[26]; u8 variant; u8 unknown31[21]; u16 resource; u8 unknown54[10]; void *visual; } Actor;
#define OFF(T,F) ((u32)&(((T*)0)->F))
typedef char actor_variant[OFF(Actor,variant)==30?1:-1];
typedef char actor_resource[OFF(Actor,resource)==52?1:-1];
typedef char actor_visual[OFF(Actor,visual)==64?1:-1];
extern Actor *FindExistingActor(void *,UnitCoordinates *);
extern u32 UnitField27HasBit12(const void *);
extern u32 UnitStateEDBit6(const void *);
extern u32 UnitField27HasBit15(const void *);
extern Actor *CreateSpecialActor(void *,UnitCoordinates *);
extern Actor *CreateSideActor(void *,UnitCoordinates *);
extern Actor *CreateDefaultActor(void *,UnitCoordinates *);
extern void InitializeActorState(Actor *);
extern u32 ResolveActorResource(UnitCoordinates *,u8 *);
extern void SetActorPosition(Actor *,s32,s32);
extern void SetActorState(Actor *,u16,s8,u32);
extern void ConfigureActorVisual(void *,u32,u32);
__asm__(".global FindExistingActor\n.thumb_set FindExistingActor,0x08099561\n");
__asm__(".global UnitField27HasBit12\n.thumb_set UnitField27HasBit12,0x080c8299\n");
__asm__(".global CreateSpecialActor\n.thumb_set CreateSpecialActor,0x0809716d\n");
__asm__(".global CreateSideActor\n.thumb_set CreateSideActor,0x08099715\n");
__asm__(".global CreateDefaultActor\n.thumb_set CreateDefaultActor,0x080996cd\n");
__asm__(".global InitializeActorState\n.thumb_set InitializeActorState,0x0809a0f5\n");
__asm__(".global ResolveActorResource\n.thumb_set ResolveActorResource,0x08022239\n");
__asm__(".global SetActorPosition\n.thumb_set SetActorPosition,0x08099e69\n");
__asm__(".global SetActorState\n.thumb_set SetActorState,0x0809836d\n");
__asm__(".global ConfigureActorVisual\n.thumb_set ConfigureActorVisual,0x08021df9\n");

/* Reuse an existing unit actor, otherwise create and initialize the selected actor class. */
Actor *FindOrCreateBattleActor(void *owner, UnitCoordinates *unit)
{
    u8 variant=0;
    Actor *actor=FindExistingActor(owner,unit);
    u32 resource;
    if (actor!=0)
        return actor;
    if ((u8)UnitField27HasBit12(unit)!=0 || (u8)UnitStateEDBit6(unit)!=0)
        actor=CreateSpecialActor(owner,unit);
    else if ((u8)UnitField27HasBit15(unit)!=0)
        actor=CreateSideActor(owner,unit);
    else
        actor=CreateDefaultActor(owner,unit);
    InitializeActorState(actor);
    resource=ResolveActorResource(unit,&variant);
    actor->variant=variant;
    actor->resource=resource;
    SetActorPosition(actor,(s8)actor->unit->x,(s8)actor->unit->y);
    SetActorState(actor,10,(s8)actor->unit->direction,0);
    ConfigureActorVisual(actor->visual,0,2);
    return actor;
}
