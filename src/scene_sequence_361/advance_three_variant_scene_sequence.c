typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *record;u8 unknown08[12];u8 definition_id;};
/* Actual creator copies a 28-byte event; the original initializes only W4. */
struct SceneChildEvent {u8 untouched00[4];void *record;u8 untouched08[20];};
struct ThreeVariantScene {u16 unknown00;u8 variant,ready;s16 x,y;void *record,*script,*resources[3],*prelude,*ready_child,*record_resource,*child,*overlay;};
struct SceneDisplayShadow {u16 control;};
extern struct SceneDisplayShadow gSceneDisplay;
extern const u8 gVariantScenePrelude[],gVariantSceneCoordinateEffect[];
extern const u8 gSceneFirstResource[],gSceneSecondResource[];
extern const u8 gVariant2FirstResource[],gVariant2SecondResource[];
extern const u8 gSceneThirdResource[],gSceneActionScript[],gSceneActionOverlay[];
extern u32 ReadRecordCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern u32 SetActorSequence(void*,u32) asm("RetailCall_080DE10C");
extern void *StartReadyActorChild(void*,u8*,u32,u32,u32,u32,u32,void*) asm("RetailCall_080DE4B0");
extern u32 StartCoordinateEffect(const void*,u32,u32,s32,s32,u32) asm("RetailCall_080D7220");
extern void *StartSceneResource(const void*,void*) asm("RetailCall_080D4704");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern u32 SceneResourcesDone(void**,u32) asm("RetailCall_080D48DC");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern void *StartRecordLayerSequence(void*,u32,u32,u32,u32,u32,void*,void*,u32,u32,void*) asm("RetailCall_080DFA70");
typedef u32 (*SceneCallback)(void*,void*,void*);
extern u32 AdvanceActorChild(void*,void*,void*) asm("RetailChild_0811C50C");
extern u32 AdvanceRingChild(void*,void*,void*) asm("RetailChild_0811C6B0");
extern void *CreateSceneChild(SceneCallback,u32,const struct SceneChildEvent*,void*) asm("RetailCall_08005B6C");
extern void *PollSceneChild(void*) asm("RetailCall_080E051C");
extern void *PollRecordResource(void*) asm("RetailCall_080DBA5C");
typedef char WorkSize[(sizeof(struct ThreeVariantScene)==48)?1:-1];
typedef char EventSize[(sizeof(struct SceneChildEvent)==28)?1:-1];
u32 AdvanceAuthoredThreeVariantScene(void*,struct SceneContext*,struct ThreeVariantScene*) asm("OriginalSceneDefinitionQuestion_0011C860");
u32 AdvanceAuthoredThreeVariantScene(void *owner,struct SceneContext *context,struct ThreeVariantScene *work)
{
    switch((s32)context->state) {
    case 0:
        work->variant=context->definition_id-125;
        work->record=context->record;
        ReadRecordCoordinates(work->record,&work->x,&work->y);
        work->prelude=StartScenePrelude(gVariantScenePrelude,8,owner);
        break;
    case 1:
        ResumeScene();
        break;
    case 256: {
        void *prelude=PollScenePrelude(work->prelude);
        work->prelude=prelude;
        if(prelude) break;
        if(work->variant==1) {
            SetActorSequence(work->record,88);
            work->ready_child=StartReadyActorChild(work->record,&work->ready,2,2,(u32)prelude,(u32)prelude,(u32)prelude,owner);
        } else work->ready=1;
        context->state++;
        break;
    }
    case 257: {
        const void *second_resource;
        if(!work->ready) break;
        StartCoordinateEffect(gVariantSceneCoordinateEffect,0,2,work->x,work->y,0);
        if(work->variant!=2) {
            work->resources[0]=StartSceneResource(gSceneFirstResource,owner);
            second_resource=gSceneSecondResource;
        } else {
            work->resources[0]=StartSceneResource(gVariant2FirstResource,owner);
            second_resource=gVariant2SecondResource;
        }
        work->resources[1]=StartSceneResource(second_resource,owner);
        work->resources[2]=StartSceneResource(gSceneThirdResource,owner);
        work->script=StartSceneScript(gSceneActionScript,owner);
        work->overlay=StartSceneOverlay(gSceneActionOverlay,1,4,0,owner);
        context->state++;
        break;
    }
    case 258:
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        if(!(u8)SceneResourcesDone(work->resources,3)) break;
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        context->state++;
        break;
    case 259: {
        struct SceneChildEvent event;
        if(work->variant!=1) {
            work->record_resource=StartRecordLayerSequence(work->record,3,7,7,1005,998,(void*)0x0600DF60,(void*)0x06005000,0,0,owner);
            if(work->variant==2) {
                event.record=work->record;
                work->child=CreateSceneChild(AdvanceRingChild,92,&event,owner);
            }
        } else {
            event.record=work->record;
            work->child=CreateSceneChild(AdvanceActorChild,28,&event,owner);
        }
        context->state++;
        break;
    }
    case 260:
        work->child=PollSceneChild(work->child);
        if(work->child) break;
        work->record_resource=PollRecordResource(work->record_resource);
        if(work->record_resource) break;
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x80035a9");

__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C, 0x8005b6d");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x80d35d9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x80d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x80d3f09");

__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x80d4705");

__asm__(".global RetailCall_080D48DC\n.thumb_set RetailCall_080D48DC, 0x80d48dd");

__asm__(".global RetailCall_080D7220\n.thumb_set RetailCall_080D7220, 0x80d7221");

__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x80d7a71");

__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x80d7abd");

__asm__(".global RetailCall_080DBA5C\n.thumb_set RetailCall_080DBA5C, 0x80dba5d");

__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8, 0x80dbdc9");

__asm__(".global RetailCall_080DE10C\n.thumb_set RetailCall_080DE10C, 0x80de10d");

__asm__(".global RetailCall_080DE4B0\n.thumb_set RetailCall_080DE4B0, 0x80de4b1");

__asm__(".global RetailCall_080DFA70\n.thumb_set RetailCall_080DFA70, 0x80dfa71");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x80dfd8d");

__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C, 0x80e051d");

__asm__(".global RetailChild_0811C50C\n.thumb_set RetailChild_0811C50C, 0x811c50d");

__asm__(".global RetailChild_0811C6B0\n.thumb_set RetailChild_0811C6B0, 0x811c6b1");

__asm__(".global gSceneDisplay\n.set gSceneDisplay, 0x3000940");

__asm__(".global gVariantScenePrelude\n.set gVariantScenePrelude, 0x83a6c7c");

__asm__(".global gVariantSceneCoordinateEffect\n.set gVariantSceneCoordinateEffect, 0x88f58ec");

__asm__(".global gSceneFirstResource\n.set gSceneFirstResource, 0x894c7e4");

__asm__(".global gSceneSecondResource\n.set gSceneSecondResource, 0x894c818");

__asm__(".global gVariant2FirstResource\n.set gVariant2FirstResource, 0x894a07c");

__asm__(".global gVariant2SecondResource\n.set gVariant2SecondResource, 0x894a0b0");

__asm__(".global gSceneThirdResource\n.set gSceneThirdResource, 0x894ac90");

__asm__(".global gSceneActionScript\n.set gSceneActionScript, 0x894d69c");

__asm__(".global gSceneActionOverlay\n.set gSceneActionOverlay, 0x83a6cdc");
