typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor;};
struct ActorStageWork {u8 unknown00[8];void *actor,*resource,*prelude,*child_a,*child_b,*child_c;};
struct SceneEvent {u32 unknown00;void *record;void **resource;u8 unknown12[16];};
extern const u8 gActorPrelude[];
extern u8 gStageVramA[],gStageVramB[];
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern void FirstActorStage(void) asm("FirstActorStageSymbol");
extern void MiddleActorStage(void) asm("MiddleActorStageSymbol");
extern void FinalActorStage(void) asm("FinalActorStageSymbol");
extern void *CreateSceneTask(void(*)(void),u32,const struct SceneEvent*,void*) asm("RetailCall_08005B6C");
extern void *PollSceneTask(void*) asm("RetailCall_080E051C");
extern u32 BeginActorPhase(void*) asm("RetailCall_080DE390");
extern u8 IsActorPhaseReady(void*) asm("RetailCall_080DE488");
extern void *StartActorStageResource(void*,u32,u32,u32,u32,u32,void*,void*,u32,u32,void*) asm("RetailCall_080DFA70");
typedef char WorkSize[(sizeof(struct ActorStageWork)==32)?1:-1];
typedef char EventSize[(sizeof(struct SceneEvent)==28)?1:-1];
u32 AdvanceThreeStageActorSequence(void*,struct SceneContext*,struct ActorStageWork*) asm("OriginalSceneDefinitionQuestion_0011DA64");
u32 AdvanceThreeStageActorSequence(void *owner,struct SceneContext *context,struct ActorStageWork *work)
{
    struct SceneEvent first_event;
    struct SceneEvent second_event;
    struct SceneEvent third_event;
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor=context->actor;
        work->prelude=StartScenePrelude(gActorPrelude,10,owner);
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256:
        work->prelude=PollScenePrelude(work->prelude);
        if(work->prelude) break;
        first_event.record=work->actor;
        work->child_a=CreateSceneTask(FirstActorStage,36,&first_event,owner);
        context->state++;
        break;
    case 257:
        work->child_a=PollSceneTask(work->child_a);
        if(work->child_a) break;
        BeginActorPhase(work->actor);
        context->state++;
        break;
    case 258:
        if(!IsActorPhaseReady(work->actor)) break;
        work->resource=StartActorStageResource(work->actor,3,7,6,882,875,gStageVramA,gStageVramB,0,127,owner);
        second_event.record=work->actor;
        second_event.resource=&work->resource;
        work->child_b=CreateSceneTask(MiddleActorStage,68,&second_event,owner);
        context->state++;
        break;
    case 259:
        work->child_b=PollSceneTask(work->child_b);
        if(work->child_b) break;
        third_event.record=work->actor;
        third_event.resource=&work->resource;
        work->child_c=CreateSceneTask(FinalActorStage,76,&third_event,owner);
        context->state++;
        break;
    case 260:
        work->child_c=PollSceneTask(work->child_c);
        if(work->child_c) break;
        context->state++;
        break;
    case 261:
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70,0x080d7a71");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC,0x080d7abd");
__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");
__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");
__asm__(".global RetailCall_080DE390\n.thumb_set RetailCall_080DE390,0x080de391");
__asm__(".global RetailCall_080DE488\n.thumb_set RetailCall_080DE488,0x080de489");
__asm__(".global RetailCall_080DFA70\n.thumb_set RetailCall_080DFA70,0x080dfa71");
__asm__(".global FirstActorStageSymbol\n.thumb_set FirstActorStageSymbol,0x0811d5fd");
__asm__(".global MiddleActorStageSymbol\n.thumb_set MiddleActorStageSymbol,0x0811d73d");
__asm__(".global FinalActorStageSymbol\n.thumb_set FinalActorStageSymbol,0x0811d8a5");
__asm__(".global gActorPrelude\n.set gActorPrelude,0x083a6eb4");
__asm__(".global gStageVramA\n.set gStageVramA,0x0600d7c0");
__asm__(".global gStageVramB\n.set gStageVramB,0x06005000");
