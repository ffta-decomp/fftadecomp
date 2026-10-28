typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *record;};
struct DefinitionRamp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct AffineActorScene {u16 counter,x,y;u8 unknown06[2];void *record,*prelude,*coordinate_resource,*script,*resource;struct DefinitionRamp angle;void *overlay;};
struct SceneAffineSource {s32 origin_x,origin_y;u16 screen_x,screen_y,scale_x,scale_y,angle;};
struct DisplayShadowBank {u16 control[4];u32 packed_pair[2];};
struct SceneDisplayShadow {u16 control;};
extern struct SceneDisplayShadow gSceneDisplay;
extern const u16 gSceneInitialXOffsets[4],gSceneAffineScales[];
extern const u8 gScenePrelude[],gScenePreludeOverlay[],gSceneCoordinateResource[];
extern const u8 gSceneScript[],gSceneResource[],gSceneMotionOverlay[];
extern void *CopySceneConstant(void*,const void*,u32) asm("RetailCall_081443FC");
extern u32 ReadRecordCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern s32 ReadActorDirection(void*) asm("RetailCall_080DBC88");
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void *GetSceneStage(void) asm("RetailCall_080D3AF8");
extern u32 SetSceneStageData(void*,u32,void*,u32) asm("RetailCall_08000B68");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern u32 SetActorSequence(void*,u32) asm("RetailCall_080DE10C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void ConfigureResourceCoordinates(u8,u8,u16,s16,s16) asm("RetailCall_080D49FC");
extern u32 ConfigureSceneResourceSlots(u32,u32,u32) asm("RetailCall_0800BC90");
extern void *CreateSceneCoordinateResource(u8,const void*,u16,u8) asm("RetailCall_080D4B64");
extern void MergeShadowControlByte(u8) asm("RetailCall_08003620");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartSceneResource(const void*,void*) asm("RetailCall_080D4704");
/* Caller-specific full-word view: original third argument is negative128.
 * The selected ramp helper consumes its low halfword; no caller zero extension. */
extern u32 InitializeSceneAngle(struct DefinitionRamp*,s32,s32,s32) asm("RetailCall_080E0608");
extern u32 AdvanceSceneAngle(struct DefinitionRamp*) asm("RetailCall_080E064C");
extern u32 SceneAngleDone(struct DefinitionRamp*) asm("RetailCall_080E0690");
extern void BuildSceneAffine(const struct SceneAffineSource*,struct DisplayShadowBank*,u32) asm("RetailCall_08141864");
extern void ApplySceneAffine(const volatile struct DisplayShadowBank*,u32) asm("RetailCall_080032F8");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern void *PollSceneResource(void*) asm("RetailCall_080D4774");
extern void *PollCoordinateResource(void*,u8) asm("RetailCall_080D4D2C");
typedef char WorkSize[(sizeof(struct AffineActorScene)==44)?1:-1];
typedef char SourceSize[(sizeof(struct SceneAffineSource)==20)?1:-1];
typedef char BankSize[(sizeof(struct DisplayShadowBank)==16)?1:-1];
u32 AdvanceAuthoredAffineActorScene(void*,struct SceneContext*,struct AffineActorScene*) asm("OriginalSceneDefinitionQuestion_0011CA70");
u32 AdvanceAuthoredAffineActorScene(void *owner,struct SceneContext *context,struct AffineActorScene *work)
{
    u16 offsets[4];
    struct SceneAffineSource source;
    struct DisplayShadowBank output;
    switch((s32)context->state) {
    case 0: {
        u8 direction;
        CopySceneConstant(offsets,gSceneInitialXOffsets,8);
        work->record=context->record;
        ReadRecordCoordinates(work->record,(s16*)&work->x,(s16*)&work->y);
        direction=(u8)ReadActorDirection(work->record);
        work->prelude=StartScenePrelude(gScenePrelude,2,owner);
        work->x+=offsets[direction];
        work->y-=38;
        SetSceneStageData(GetSceneStage(),0,(void*)0x0600FFC0,16);
        break;
    }
    case 1:
        ResumeScene();
        break;
    case 256:
        work->prelude=PollScenePrelude(work->prelude);
        if(work->prelude) break;
        SetActorSequence(work->record,24);
        work->overlay=StartSceneOverlay(gScenePreludeOverlay,1,4,0,owner);
        work->counter=20;
        context->state++;
        break;
    case 257:
        work->counter--;
        if(work->counter) break;
        ConfigureResourceCoordinates(0,2,1,(s16)work->x,(s16)work->y);
        ConfigureSceneResourceSlots(0,0,2);
        work->coordinate_resource=CreateSceneCoordinateResource(0,gSceneCoordinateResource,186,6);
        MergeShadowControlByte(1);
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control|=mask;
            gSceneDisplay.control=control;
        }
        work->script=StartSceneScript(gSceneScript,owner);
        work->resource=StartSceneResource(gSceneResource,owner);
        InitializeSceneAngle(&work->angle,0,-128,28);
        work->overlay=StartSceneOverlay(gSceneMotionOverlay,1,4,0,owner);
        context->state++;
        break;
    case 258: {
        struct DefinitionRamp *angle=&work->angle;
        AdvanceSceneAngle(angle);
        source.origin_x=0x2000;
        source.origin_y=0x3000;
        source.screen_x=work->x;
        source.screen_y=work->y;
        source.scale_x=gSceneAffineScales[work->counter];
        source.scale_y=gSceneAffineScales[work->counter];
        source.angle=work->angle.value<<8;
        BuildSceneAffine(&source,&output,1);
        ApplySceneAffine(&output,2);
        work->counter++;
        if((u8)SceneAngleDone(angle)) context->state++;
        break;
    }
    case 259:
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        work->resource=PollSceneResource(work->resource);
        if(work->resource) break;
        work->coordinate_resource=PollCoordinateResource(work->coordinate_resource,0);
        if(work->coordinate_resource) break;
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        MergeShadowControlByte(0);
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_08000B68\n.thumb_set RetailCall_08000B68, 0x8000b69");

__asm__(".global RetailCall_080032F8\n.thumb_set RetailCall_080032F8, 0x80032f9");

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x80035a9");

__asm__(".global RetailCall_08003620\n.thumb_set RetailCall_08003620, 0x8003621");

__asm__(".global RetailCall_0800BC90\n.thumb_set RetailCall_0800BC90, 0x800bc91");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x80d35d9");

__asm__(".global RetailCall_080D3AF8\n.thumb_set RetailCall_080D3AF8, 0x80d3af9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x80d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x80d3f09");

__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x80d4705");

__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774, 0x80d4775");

__asm__(".global RetailCall_080D49FC\n.thumb_set RetailCall_080D49FC, 0x80d49fd");

__asm__(".global RetailCall_080D4B64\n.thumb_set RetailCall_080D4B64, 0x80d4b65");

__asm__(".global RetailCall_080D4D2C\n.thumb_set RetailCall_080D4D2C, 0x80d4d2d");

__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x80d7a71");

__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x80d7abd");

__asm__(".global RetailCall_080DBC88\n.thumb_set RetailCall_080DBC88, 0x80dbc89");

__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8, 0x80dbdc9");

__asm__(".global RetailCall_080DE10C\n.thumb_set RetailCall_080DE10C, 0x80de10d");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x80dfd8d");

__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608, 0x80e0609");

__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C, 0x80e064d");

__asm__(".global RetailCall_080E0690\n.thumb_set RetailCall_080E0690, 0x80e0691");

__asm__(".global RetailCall_08141864\n.thumb_set RetailCall_08141864, 0x8141865");

__asm__(".global RetailCall_081443FC\n.thumb_set RetailCall_081443FC, 0x81443fd");

__asm__(".global gSceneDisplay\n.set gSceneDisplay, 0x3000940");

__asm__(".global gSceneInitialXOffsets\n.set gSceneInitialXOffsets, 0x8149fa4");

__asm__(".global gSceneAffineScales\n.set gSceneAffineScales, 0x83a6d1c");

__asm__(".global gScenePrelude\n.set gScenePrelude, 0x83a6d04");

__asm__(".global gScenePreludeOverlay\n.set gScenePreludeOverlay, 0x83a6d5c");

__asm__(".global gSceneCoordinateResource\n.set gSceneCoordinateResource, 0x88f104c");

__asm__(".global gSceneScript\n.set gSceneScript, 0x894db48");

__asm__(".global gSceneResource\n.set gSceneResource, 0x8949f18");

__asm__(".global gSceneMotionOverlay\n.set gSceneMotionOverlay, 0x83a6d54");
