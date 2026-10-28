typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *record,*other_record;};
struct PairedRecordScene {u16 delay,x,y;u8 unknown06[2];void *record,*other_record,*child;u8 unknown_output20[8];void *script,*resource,*prelude,*overlay;};
struct SceneDisplayShadow {u16 control;};
extern struct SceneDisplayShadow gSceneDisplay;
extern u16 gSceneZeroBuffer[16];
extern const u8 gScenePrelude[],gScenePreludeOverlay[],gProjectedSequence[],gProjectedOverlay[];
extern const u8 gSceneCoordinateEffect[],gSceneResource[],gSceneScript[];
extern void ReadRecordCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void CpuSetSceneData(const void*,void*,u32) asm("RetailCall_0814186C");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern u32 SetActorSequence(void*,u32) asm("RetailCall_080DE10C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
/* Actual caller passes both coordinates as sign-extended words; the selected
 * helper stores the second coordinate's LOW16 through its u16 formal view. */
extern void *StartPositionedSequence(s32,s32,s32,u8,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern u32 StartCoordinateEffect(const void*,u32,u32,s32,s32,u32) asm("RetailCall_080D7220");
extern void *StartSceneResource(const void*,void*) asm("RetailCall_080D4704");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void ChangeRecordFlag(void*,u8) asm("RetailCall_080DBEB4");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern void *PollSceneResource(void*) asm("RetailCall_080D4774");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern u32 ClearSceneStage(void) asm("RetailCall_080D4020");
extern void *PollPositionedSequence(void*) asm("RetailCall_080D6134");
typedef char WorkSize[(sizeof(struct PairedRecordScene)==44)?1:-1];
u32 AdvancePairedRecordProjectedScene(void*,struct SceneContext*,struct PairedRecordScene*) asm("OriginalSceneDefinitionQuestion_0011DDF0");
u32 AdvancePairedRecordProjectedScene(void *owner,struct SceneContext *context,struct PairedRecordScene *work)
{
    u16 fill;
    s32 state=context->state;
    switch(state) {
    case 0:
        work->record=context->record;
        work->other_record=context->other_record;
        ReadRecordCoordinates(work->record,(s16*)&work->x,(s16*)&work->y);
        work->prelude=StartScenePrelude(gScenePrelude,4,owner);
        /* The actual zero state snapshot survives the prelude call. */
        fill=state;
        CpuSetSceneData(&fill,gSceneZeroBuffer,0x01000010);
        break;
    case 1:
        ResumeScene();
        break;
    case 256:
        work->prelude=PollScenePrelude(work->prelude);
        if(work->prelude) break;
        SetActorSequence(work->record,88);
        work->overlay=StartSceneOverlay(gScenePreludeOverlay,1,4,0,owner);
        work->delay=20;
        context->state++;
        break;
    case 257:
        work->delay--;
        if(work->delay) break;
        work->child=StartPositionedSequence((s16)(work->x+11),(s16)(work->y-31),0,1,2,(u8*)work+20,gProjectedSequence,owner);
        work->overlay=StartSceneOverlay(gProjectedOverlay,1,4,0,owner);
        work->delay=12;
        context->state++;
        break;
    case 258: {
        u32 remaining=--work->delay;
        if(remaining) break;
        StartCoordinateEffect(gSceneCoordinateEffect,0,2,(s16)(work->x+11),(s16)(work->y-31),remaining);
        work->resource=StartSceneResource(gSceneResource,owner);
        work->script=StartSceneScript(gSceneScript,owner);
        work->delay=130;
        context->state++;
        break;
    }
    case 259:
        if(work->delay) {
            work->delay--;
            if(!work->delay) {
                ChangeRecordFlag(work->record,0);
                ChangeRecordFlag(work->other_record,0);
            }
        }
        /* Completion polling runs while the independent flag timer counts. */
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        work->resource=PollSceneResource(work->resource);
        if(work->resource) break;
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        ClearSceneStage();
        work->child=PollPositionedSequence(work->child);
        if(work->child) break;
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x80035a9");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x80d35d9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x80d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x80d3f09");

__asm__(".global RetailCall_080D4020\n.thumb_set RetailCall_080D4020, 0x80d4021");

__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x80d4705");

__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774, 0x80d4775");

__asm__(".global RetailCall_080D6098\n.thumb_set RetailCall_080D6098, 0x80d6099");

__asm__(".global RetailCall_080D6134\n.thumb_set RetailCall_080D6134, 0x80d6135");

__asm__(".global RetailCall_080D7220\n.thumb_set RetailCall_080D7220, 0x80d7221");

__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x80d7a71");

__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x80d7abd");

__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8, 0x80dbdc9");

__asm__(".global RetailCall_080DBEB4\n.thumb_set RetailCall_080DBEB4, 0x80dbeb5");

__asm__(".global RetailCall_080DE10C\n.thumb_set RetailCall_080DE10C, 0x80de10d");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x80dfd8d");

__asm__(".global RetailCall_0814186C\n.thumb_set RetailCall_0814186C, 0x814186d");

__asm__(".global gSceneDisplay\n.set gSceneDisplay, 0x3000940");

__asm__(".global gSceneZeroBuffer\n.set gSceneZeroBuffer, 0x3003920");

__asm__(".global gScenePrelude\n.set gScenePrelude, 0x83a7248");

__asm__(".global gScenePreludeOverlay\n.set gScenePreludeOverlay, 0x83a72b0");

__asm__(".global gProjectedSequence\n.set gProjectedSequence, 0x83a7278");

__asm__(".global gProjectedOverlay\n.set gProjectedOverlay, 0x83a72a8");

__asm__(".global gSceneCoordinateEffect\n.set gSceneCoordinateEffect, 0x88f4e9c");

__asm__(".global gSceneResource\n.set gSceneResource, 0x894c93c");

__asm__(".global gSceneScript\n.set gSceneScript, 0x894d69c");
