typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[18];s16 definition;};
struct SceneInterpolation {u16 value;u8 unknown02[10];};
struct VariantWindowSceneSequence {
    u8 variant,child_kind,skip_deformation,shake;
    u16 countdown;u8 phase_countdown,unknown07[5];
    u8 phase_a,phase_b,unknown14[2];
    void *child,*effect,*companion,*script;
    struct SceneInterpolation radius;
    void *overlay;
};
struct SceneDisplayShadow {
    u16 control;u8 unknown02[16];volatile u16 horizontal18;
    u8 unknown20[2];volatile u16 horizontal22;
    u8 unknown24[50];volatile u8 byte74;u8 unknown75[3];volatile u8 byte78;
};
extern struct SceneDisplayShadow gSceneDisplay;
extern const u8 gSceneWindowOverlayA[],gSceneWindowOverlayB[];
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940\n.global gSceneWindowOverlayA\n.set gSceneWindowOverlayA,0x083A6C08\n.global gSceneWindowOverlayB\n.set gSceneWindowOverlayB,0x083A6C00");
extern u32 SetSceneResource(const void*,u32,u32,u32,u32) asm("RetailCall_080D45D0");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *StartSceneChild(u8,void*) asm("RetailCall_0811ECD0");
extern void *PollSceneChild(void*) asm("RetailCall_0811ED14");
extern void *CreateSceneEffectObject(void*) asm("RetailCall_0811EC30");
extern u32 InitializeSceneInterpolation(struct SceneInterpolation*,s32,s32,s32) asm("RetailCall_080E0608");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *CreateSceneCompanion(u32,u32,u32,const void*,void*) asm("RetailCall_080D979C");
extern u32 AdvanceSceneInterpolation(struct SceneInterpolation*) asm("RetailCall_080E064C");
extern void ApplySceneWindowPhase(void*,u8,u8*,u8*,u8*,u8) asm("RetailCall_0811BEC0");
extern u32 SceneInterpolationDone(struct SceneInterpolation*) asm("RetailCall_080E0690");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern u32 SetSceneStageParameter(u32) asm("RetailCall_080D3AC0");
extern u32 PrepareSceneEffectEnd(void*) asm("RetailCall_080DADFC");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern void *DeleteSceneEffect(void*) asm("RetailCall_080D9B64");
typedef char WorkSize[(sizeof(struct VariantWindowSceneSequence)==48)?1:-1];
typedef char InterpolationSize[(sizeof(struct SceneInterpolation)==12)?1:-1];
u32 AdvanceVariantWindowSceneSequence(void*,struct SceneContext*,struct VariantWindowSceneSequence*) asm("OriginalSceneDefinitionQuestion_0011C018");
u32 AdvanceVariantWindowSceneSequence(void *owner,struct SceneContext *context,struct VariantWindowSceneSequence *work)
{
    switch(context->state) {
    case 0:
        work->child_kind=1;
        work->shake=0;
        work->skip_deformation=0;
        work->variant=0;
        if(context->definition==375) {
            work->variant=1;
            work->skip_deformation=1;
        }
        SetSceneResource((void*)0x088EB4A4,6,0,0,1);
        break;
    case 1:
        ResumeScene();
        break;
    case 256:
        work->child=StartSceneChild(work->child_kind,owner);
        context->state++;
        break;
    case 257:
        work->child=PollSceneChild(work->child);
        if(work->child) break;
        work->effect=CreateSceneEffectObject(owner);
        if(!work->variant) {
            InitializeSceneInterpolation(&work->radius,0,32,30);
            work->overlay=StartSceneOverlay(gSceneWindowOverlayA,1,4,0,owner);
        } else {
            InitializeSceneInterpolation(&work->radius,0,145,60);
            work->script=StartSceneScript((void*)0x0894DD64,owner);
            work->overlay=StartSceneOverlay(gSceneWindowOverlayB,1,4,0,owner);
        }
        if(!work->shake)
            work->companion=CreateSceneCompanion(2,2,0,(void*)0x083A6BF0,owner);
        work->phase_a=19;
        work->phase_b=0;
        work->phase_countdown=1;
        context->state++;
        break;
    case 258: {
        struct SceneInterpolation *radius=&work->radius;
        AdvanceSceneInterpolation(radius);
        ApplySceneWindowPhase(work->effect,(u8)work->radius.value,&work->phase_a,&work->phase_b,&work->phase_countdown,work->skip_deformation);
        if(!(u8)SceneInterpolationDone(radius)) break;
        work->countdown=60;
        if(work->variant==1) {
            {
                u32 mask=SceneLayerMask(2);
                u32 control=gSceneDisplay.control;
                control&=~mask;
                gSceneDisplay.control=control;
            }
            {
                u32 mask=SceneLayerMask(3);
                u32 control=gSceneDisplay.control;
                control&=~mask;
                control&=0xDFFF;
                gSceneDisplay.control=control;
            }
            gSceneDisplay.byte74=255;
            gSceneDisplay.byte78=16;
            SetSceneStageParameter(0);
            context->state=261;
        } else context->state++;
        break;
    }
    case 259:
        ApplySceneWindowPhase(work->effect,(u8)work->radius.value,&work->phase_a,&work->phase_b,&work->phase_countdown,work->skip_deformation);
        if(work->shake && work->countdown<=40) {
            if(work->countdown&2) {
                gSceneDisplay.horizontal18+=2;
                gSceneDisplay.horizontal22+=2;
            } else {
                gSceneDisplay.horizontal18-=2;
                gSceneDisplay.horizontal22-=2;
            }
        }
        work->countdown--;
        if(work->countdown) break;
        InitializeSceneInterpolation(&work->radius,32,0,30);
        context->state++;
        break;
    case 260: {
        struct SceneInterpolation *radius=&work->radius;
        AdvanceSceneInterpolation(radius);
        PrepareSceneEffectEnd(work->effect);
        ApplySceneWindowPhase(work->effect,(u8)work->radius.value,&work->phase_a,&work->phase_b,&work->phase_countdown,work->skip_deformation);
        if(!(u8)SceneInterpolationDone(radius)) break;
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            control&=0xDFFF;
            gSceneDisplay.control=control;
        }
        gSceneDisplay.byte74=0;
        context->state++;
        break;
    }
    case 261:
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        work->effect=DeleteSceneEffect(work->effect);
        if(work->effect) break;
        work->companion=DeleteSceneEffect(work->companion);
        if(work->companion) break;
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D3AC0\n.thumb_set RetailCall_080D3AC0, 0x080d3ac1");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x080d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x080d3f09");

__asm__(".global RetailCall_080D45D0\n.thumb_set RetailCall_080D45D0, 0x080d45d1");

__asm__(".global RetailCall_080D979C\n.thumb_set RetailCall_080D979C, 0x080d979d");

__asm__(".global RetailCall_080D9B64\n.thumb_set RetailCall_080D9B64, 0x080d9b65");

__asm__(".global RetailCall_080DADFC\n.thumb_set RetailCall_080DADFC, 0x080dadfd");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608, 0x080e0609");

__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C, 0x080e064d");

__asm__(".global RetailCall_080E0690\n.thumb_set RetailCall_080E0690, 0x080e0691");

__asm__(".global RetailCall_0811BEC0\n.thumb_set RetailCall_0811BEC0, 0x0811bec1");

__asm__(".global RetailCall_0811EC30\n.thumb_set RetailCall_0811EC30, 0x0811ec31");

__asm__(".global RetailCall_0811ECD0\n.thumb_set RetailCall_0811ECD0, 0x0811ecd1");

__asm__(".global RetailCall_0811ED14\n.thumb_set RetailCall_0811ED14, 0x0811ed15");
