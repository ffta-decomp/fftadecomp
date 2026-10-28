typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct SceneRequest { u8 command; u8 active; u8 request_flags; u8 request_index; u16 scene_id; u8 substate; u8 unaccessed_07[6]; u8 countdown; };
struct SceneActor { u8 unaccessed_00[64]; void *request_object; };
typedef char CountdownOffset[(u32)&(((struct SceneRequest *)0)->countdown)==13?1:-1];
extern struct SceneRequest gSceneRequest;
extern void *gSelectedSceneUnit;
extern void *gSelectedSceneObject;
extern struct TaskNode *GetUnitTaskHandle(u32);
extern u32 ReadUnitTaskState(struct TaskNode *);
extern void BeginSceneRequestTransition(u16,u8);
extern void *GetSelectedBattleUnit(void);
extern void *GetBattleActionRegistry(void);
extern struct SceneActor *FindPrimaryActor(void *,const void *);
u32 AdvanceSelectedUnitSceneRequest(void)
{
    struct SceneActor *actor;
    switch(gSceneRequest.substate) {
    case 0:
        if((ReadUnitTaskState(GetUnitTaskHandle(1))&3)==3)
            gSceneRequest.substate=1;
        break;
    case 1:
        BeginSceneRequestTransition(8,16);
        gSceneRequest.command=19;
        gSelectedSceneUnit=GetSelectedBattleUnit();
        actor=FindPrimaryActor(GetBattleActionRegistry(),gSelectedSceneUnit);
        if(actor!=0)gSelectedSceneObject=actor->request_object;
        else gSelectedSceneObject=0;
        gSceneRequest.substate=2;
        break;
    case 2:
        if(gSceneRequest.command==0) {
            gSceneRequest.countdown=4;
            gSceneRequest.substate=3;
        }
        break;
    case 3:
        if(gSceneRequest.countdown!=0) {
            gSceneRequest.countdown--;
            if(gSceneRequest.countdown!=0)break;
        }
        gSceneRequest.request_flags=128;
        gSceneRequest.active=0;
        return 1;
    }
    return 18;
}
asm(".global gSceneRequest\n.set gSceneRequest,0x0200f390\n"
    ".global gSelectedSceneUnit\n.set gSelectedSceneUnit,0x030027f4\n"
    ".global gSelectedSceneObject\n.set gSelectedSceneObject,0x030027d4\n"
    ".global GetUnitTaskHandle\n.thumb_set GetUnitTaskHandle,0x0802d72d\n"
    ".global ReadUnitTaskState\n.thumb_set ReadUnitTaskState,0x0802b881\n"
    ".global BeginSceneRequestTransition\n.thumb_set BeginSceneRequestTransition,0x08022cd5\n"
    ".global GetSelectedBattleUnit\n.thumb_set GetSelectedBattleUnit,0x080294fd\n"
    ".global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n"
    ".global FindPrimaryActor\n.thumb_set FindPrimaryActor,0x08099561\n");
