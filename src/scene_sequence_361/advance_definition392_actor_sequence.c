typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor_a,*actor_b;};
struct TwoActorSequence {u16 timer;s16 x,y;u8 unknown06[2];void *child,*transition,*actor_a,*actor_b,*prelude;u8 unknown28[4];};
struct SceneEvent {u32 unknown00;void *record;u8 unknown08[20];};
extern const u8 gActorPrelude[];
extern u16 gScenePalette[];
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void CpuSet(const void*,void*,u32) asm("RetailCall_0814186C");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern void ChildActorSequence(void) asm("ChildActorSequenceSymbol");
extern void *CreateSceneTask(void(*)(void),u32,const struct SceneEvent*,void*) asm("RetailCall_08005B6C");
extern void *PollSceneTask(void*) asm("RetailCall_080E051C");
extern void *StartSceneTransition(void*) asm("RetailCall_080E5694");
extern void SetActorPhaseFlag(void*,u32) asm("RetailCall_080DBEB4");
extern void SetActorMode(void*,u32) asm("RetailCall_080DD720");
extern void SetActorPose(void*,u32) asm("RetailCall_080DE10C");
extern void *GetActorResource(void*) asm("RetailCall_080DD350");
extern void UpdateResourceFlags(void*,u32,u32) asm("RetailCall_0809A570");
extern void SetResourceMode(void*,u32) asm("RetailCall_0809A530");
extern void SetActorSequenceFrame(void*,u32,u32) asm("RetailCall_080DE150");
typedef char WorkSize[(sizeof(struct TwoActorSequence)==32)?1:-1];
typedef char EventSize[(sizeof(struct SceneEvent)==28)?1:-1];
u32 AdvanceTwoActorSequence(void*,struct SceneContext*,struct TwoActorSequence*) asm("OriginalSceneDefinitionQuestion_0011D4A0");
u32 AdvanceTwoActorSequence(void *owner,struct SceneContext *context,struct TwoActorSequence *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor_a=context->actor_a;
        work->actor_b=context->actor_b;
        ReadActorCoordinates(work->actor_a,&work->x,&work->y);
        work->prelude=StartScenePrelude(gActorPrelude,8,owner);
        {
            volatile u16 fill=(volatile u16)0x7fff;
            CpuSet((const void*)&fill,gScenePalette,0x01000010);
        }
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256: {
        struct SceneEvent event;
        work->prelude=PollScenePrelude(work->prelude);
        if(work->prelude) break;
        event.record=work->actor_a;
        work->child=CreateSceneTask(ChildActorSequence,64,&event,owner);
        work->timer=10;
        context->state++;
        break;
    }
    case 257:
        work->child=PollSceneTask(work->child);
        if(work->child) break;
        if(work->timer && --work->timer) break;
        work->transition=StartSceneTransition(owner);
        work->timer=20;
        context->state++;
        break;
    case 258:
        if(work->timer && !--work->timer) {
            void *resource;
            SetActorPhaseFlag(work->actor_a,0);
            SetActorPhaseFlag(work->actor_b,1);
            SetActorMode(work->actor_b,2);
            SetActorPose(work->actor_b,60);
            resource=GetActorResource(work->actor_b);
            UpdateResourceFlags(resource,0,256);
            SetResourceMode(resource,2);
        }
        work->transition=PollSceneTask(work->transition);
        if(!work->transition) {
            work->timer=40;
            context->state++;
        }
        break;
    case 259:
        if(!--work->timer) {
            SetActorSequenceFrame(work->actor_b,0,0);
            context->state=2;
        }
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");
__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70,0x080d7a71");
__asm__(".global RetailCall_0814186C\n.thumb_set RetailCall_0814186C,0x0814186d");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC,0x080d7abd");
__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");
__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");
__asm__(".global RetailCall_080E5694\n.thumb_set RetailCall_080E5694,0x080e5695");
__asm__(".global RetailCall_080DBEB4\n.thumb_set RetailCall_080DBEB4,0x080dbeb5");
__asm__(".global RetailCall_080DD720\n.thumb_set RetailCall_080DD720,0x080dd721");
__asm__(".global RetailCall_080DE10C\n.thumb_set RetailCall_080DE10C,0x080de10d");
__asm__(".global RetailCall_080DD350\n.thumb_set RetailCall_080DD350,0x080dd351");
__asm__(".global RetailCall_0809A570\n.thumb_set RetailCall_0809A570,0x0809a571");
__asm__(".global RetailCall_0809A530\n.thumb_set RetailCall_0809A530,0x0809a531");
__asm__(".global RetailCall_080DE150\n.thumb_set RetailCall_080DE150,0x080de151");
__asm__(".global ChildActorSequenceSymbol\n.thumb_set ChildActorSequenceSymbol,0x0811d219");
__asm__(".global gActorPrelude\n.set gActorPrelude,0x083a6dc4");
__asm__(".global gScenePalette\n.set gScenePalette,0x03003940");
