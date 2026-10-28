typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor;};
struct ActorWindowWork {
    u16 timer;s16 x,y;u8 unknown06[2];
    void *child,*actor,*positioned,*positioned_output;
    void *resource_a,*resource_b,*prelude,*overlay;
};
struct SceneEvent {u32 unknown00;void *actor;u8 unknown08[12];u16 definition,selector;u8 unknown24[4];};
struct SceneDisplayShadow {u16 control;u8 unknown02[66];volatile u8 inside,outside;};
extern struct SceneDisplayShadow gSceneDisplay;
extern u16 gScenePalette[32];
extern const u8 gActorPrelude[],gSceneOverlay[],gPositionedSequence[],gEffectProgram[],gResourceA[],gResourceB[];
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void CpuSet(const void*,void*,u32) asm("RetailCall_0814186C");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern void ActorDefinitionCallback(void) asm("ActorDefinitionCallbackSymbol");
extern void *CreateSceneTask(void(*)(void),u32,const struct SceneEvent*,void*) asm("RetailCall_08005B6C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *PollSceneTask(void*) asm("RetailCall_080E051C");
extern void *StartPositionedSequence(s32,s32,s32,u8,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern u32 ReadWindowMask(u32) asm("RetailCall_080035D0");
extern void StartEffectProgram(const void*,u32,u32,s32,s32,u32) asm("RetailCall_080D7220");
extern void *StartSecondaryResource(const void*,void*) asm("RetailCall_080D4704");
extern void *StartEffectResource(const void*,void*) asm("RetailCall_080D3E9C");
extern void *PollEffectResource(void*) asm("RetailCall_080D3F08");
extern void *PollSecondaryResource(void*) asm("RetailCall_080D4774");
extern u32 ReadLayerDisableMask(u32) asm("RetailCall_080035A8");
extern void ClearSceneStage(void) asm("RetailCall_080D4020");
extern void *PollPositionedSequence(void*) asm("RetailCall_080D6134");
typedef char WorkSize[(sizeof(struct ActorWindowWork)==40)?1:-1];
typedef char EventSize[(sizeof(struct SceneEvent)==28)?1:-1];
u32 AdvanceActorWindowResources(void*,struct SceneContext*,struct ActorWindowWork*) asm("OriginalSceneDefinitionQuestion_0011E034");
u32 AdvanceActorWindowResources(void *owner,struct SceneContext *context,struct ActorWindowWork *work)
{
    s32 state=context->state;
    switch(state) {
    case 0: {
        work->actor=context->actor;
        ReadActorCoordinates(work->actor,&work->x,&work->y);
        work->prelude=StartScenePrelude(gActorPrelude,3,owner);
        {
            volatile u16 fill=(volatile u16)0x7fff;
            CpuSet((const void*)&fill,gScenePalette,0x01000010);
        }
        break;
    }
    case 1:
        RestoreSceneStage();
        break;
    case 256: {
        struct SceneEvent event;
        void *completed=PollScenePrelude(work->prelude);
        work->prelude=completed;
        if(completed) break;
        event.definition=396;
        event.selector=(u16)(u32)completed;
        event.actor=work->actor;
        work->child=CreateSceneTask(ActorDefinitionCallback,112,&event,owner);
        work->overlay=StartSceneOverlay(gSceneOverlay,1,4,0,owner);
        work->timer=20;
        context->state++;
        break;
    }
    case 257: {
        void *completed=PollSceneTask(work->child);
        u32 mask;
        work->child=completed;
        if(completed) break;
        if(work->timer && --work->timer) break;
        work->positioned=StartPositionedSequence(work->x,work->y,0,1,1,&work->positioned_output,gPositionedSequence,owner);
        mask=ReadWindowMask(2);
        gSceneDisplay.inside=63&~mask;
        gSceneDisplay.outside=63;
        gSceneDisplay.control|=0x8000;
        StartEffectProgram(gEffectProgram,0,2,0,(s32)completed,(u32)completed);
        work->resource_b=StartSecondaryResource(gResourceB,owner);
        work->resource_a=StartEffectResource(gResourceA,owner);
        context->state++;
        break;
    }
    case 258: {
        u32 mask;
        work->resource_a=PollEffectResource(work->resource_a);
        if(work->resource_a) break;
        work->resource_b=PollSecondaryResource(work->resource_b);
        if(work->resource_b) break;
        mask=ReadLayerDisableMask(2);
        gSceneDisplay.control&=~mask;
        ClearSceneStage();
        gSceneDisplay.control&=0x7fff;
        work->positioned=PollPositionedSequence(work->positioned);
        if(work->positioned) break;
        context->state=2;
        break;
    }
    }
    return 0;
}
__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");
__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70,0x080d7a71");
__asm__(".global RetailCall_0814186C\n.thumb_set RetailCall_0814186C,0x0814186d");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC,0x080d7abd");
__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");
__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");
__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");
__asm__(".global RetailCall_080D6098\n.thumb_set RetailCall_080D6098,0x080d6099");
__asm__(".global RetailCall_080035D0\n.thumb_set RetailCall_080035D0,0x080035d1");
__asm__(".global RetailCall_080D7220\n.thumb_set RetailCall_080D7220,0x080d7221");
__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704,0x080d4705");
__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C,0x080d3e9d");
__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08,0x080d3f09");
__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774,0x080d4775");
__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8,0x080035a9");
__asm__(".global RetailCall_080D4020\n.thumb_set RetailCall_080D4020,0x080d4021");
__asm__(".global RetailCall_080D6134\n.thumb_set RetailCall_080D6134,0x080d6135");
__asm__(".global ActorDefinitionCallbackSymbol\n.thumb_set ActorDefinitionCallbackSymbol,0x080e9555");
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940");
__asm__(".global gScenePalette\n.set gScenePalette,0x03003920");
__asm__(".global gActorPrelude\n.set gActorPrelude,0x083a72d0");
__asm__(".global gSceneOverlay\n.set gSceneOverlay,0x083a730c");
__asm__(".global gPositionedSequence\n.set gPositionedSequence,0x083a72f4");
__asm__(".global gEffectProgram\n.set gEffectProgram,0x088f46cc");
__asm__(".global gResourceA\n.set gResourceA,0x0894d69c");
__asm__(".global gResourceB\n.set gResourceB,0x0894c6a8");
