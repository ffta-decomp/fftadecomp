typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor;};
struct ActorPerformanceWork {
    u8 unknown00[2];s16 x,y;u8 unknown06[2];
    void *actor,*scene_object,*resource,*secondary_a,*secondary_b,*performance,*overlay;
};
extern u16 gSceneDisplayFlags;
extern const u8 gSceneObjectDefinition[],gEffectResource[],gSecondaryA[],gSecondaryB[],gSceneOverlay[];
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern u32 SetSceneObjectPosition(u32,u32,u32,s16,s16) asm("RetailCall_080D49FC");
extern void *CreateSceneObject(u32,const void*,u32,u32) asm("RetailCall_080D4B64");
extern u32 ReadSceneLayerMask(u32) asm("RetailCall_080035A8");
extern void *StartEffectResource(const void*,void*) asm("RetailCall_080D3E9C");
extern void SetResourceParameter(void*,u32,u32) asm("RetailCall_080D3F84");
extern void *StartSecondaryResource(const void*,void*) asm("RetailCall_080D4704");
extern void *StartActorPerformance(void*,u32,u32,u32,void*) asm("RetailCall_080DBB14");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *PollSceneObject(void*,u32) asm("RetailCall_080D4D2C");
extern void *PollEffectResource(void*) asm("RetailCall_080D3F08");
extern void *PollSecondaryResource(void*) asm("RetailCall_080D4774");
extern void ClearSceneStage(void) asm("RetailCall_080D4020");
extern void *PollActorPerformance(void*) asm("RetailCall_080DBA5C");
typedef char WorkSize[(sizeof(struct ActorPerformanceWork)==36)?1:-1];
u32 AdvanceActorSevenFrameTwelveEffect(void*,struct SceneContext*,struct ActorPerformanceWork*) asm("RemainingBand43_0011D5FC");
u32 AdvanceActorSevenFrameTwelveEffect(void *owner,struct SceneContext *context,struct ActorPerformanceWork *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor=context->actor;
        ReadActorCoordinates(work->actor,&work->x,&work->y);
        break;
    case 256: {
        u32 mask;
        SetSceneObjectPosition(1,3,0,0,0);
        work->scene_object=CreateSceneObject(1,gSceneObjectDefinition,812,7);
        mask=ReadSceneLayerMask(3);
        {
            u32 control=gSceneDisplayFlags;
            control|=mask;
            gSceneDisplayFlags=control;
        }
        work->resource=StartEffectResource(gEffectResource,owner);
        SetResourceParameter(work->resource,8,255);
        work->secondary_a=StartSecondaryResource(gSecondaryA,owner);
        work->secondary_b=StartSecondaryResource(gSecondaryB,owner);
        work->performance=StartActorPerformance(work->actor,7,12,0,owner);
        work->overlay=StartSceneOverlay(gSceneOverlay,1,4,0,owner);
        context->state++;
        break;
    }
    case 257: {
        u32 mask;
        work->scene_object=PollSceneObject(work->scene_object,1);
        if(work->scene_object) break;
        work->resource=PollEffectResource(work->resource);
        if(work->resource) break;
        work->secondary_a=PollSecondaryResource(work->secondary_a);
        if(work->secondary_a) break;
        work->secondary_b=PollSecondaryResource(work->secondary_b);
        if(work->secondary_b) break;
        mask=ReadSceneLayerMask(3);
        gSceneDisplayFlags&=~mask;
        ClearSceneStage();
        work->performance=PollActorPerformance(work->performance);
        if(work->performance) break;
        context->state++;
        break;
    }
    case 258:
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");
__asm__(".global RetailCall_080D49FC\n.thumb_set RetailCall_080D49FC,0x080d49fd");
__asm__(".global RetailCall_080D4B64\n.thumb_set RetailCall_080D4B64,0x080d4b65");
__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8,0x080035a9");
__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C,0x080d3e9d");
__asm__(".global RetailCall_080D3F84\n.thumb_set RetailCall_080D3F84,0x080d3f85");
__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704,0x080d4705");
__asm__(".global RetailCall_080DBB14\n.thumb_set RetailCall_080DBB14,0x080dbb15");
__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");
__asm__(".global RetailCall_080D4D2C\n.thumb_set RetailCall_080D4D2C,0x080d4d2d");
__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08,0x080d3f09");
__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774,0x080d4775");
__asm__(".global RetailCall_080D4020\n.thumb_set RetailCall_080D4020,0x080d4021");
__asm__(".global RetailCall_080DBA5C\n.thumb_set RetailCall_080DBA5C,0x080dba5d");
__asm__(".global gSceneDisplayFlags\n.set gSceneDisplayFlags,0x03000940");
__asm__(".global gSceneObjectDefinition\n.set gSceneObjectDefinition,0x088f1b54");
__asm__(".global gEffectResource\n.set gEffectResource,0x0894d6a8");
__asm__(".global gSecondaryA\n.set gSecondaryA,0x0894c9b0");
__asm__(".global gSecondaryB\n.set gSecondaryB,0x0894ac90");
__asm__(".global gSceneOverlay\n.set gSceneOverlay,0x083a70ac");
