typedef unsigned int u32;
struct SceneActor { unsigned char unaccessed_00[48]; u32 flags; };
extern void *GetBattleActionRegistry(void);
extern struct SceneActor *FindPrimaryActor(void *,const void *);
u32 ReadBattleUnitActorFlag15(const void *unit)
{
    struct SceneActor *actor=FindPrimaryActor(GetBattleActionRegistry(),unit);
    return (actor->flags>>15)&1;
}
asm(".global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n"
    ".global FindPrimaryActor\n.thumb_set FindPrimaryActor,0x08099561\n");
