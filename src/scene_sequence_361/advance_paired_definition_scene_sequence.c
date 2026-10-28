typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *definition;u8 unknown08[12];u8 definition_id;};
struct SceneInterpolation {u16 value;u8 unknown02[10];};
struct SceneCoordinates {s16 x,y;};
struct SceneCoordinatePair {struct SceneCoordinates values[2];};
struct VariantSceneSequence {
    u16 delay;u8 variant,unknown03;s16 x,y;
    void *definition,*object,*script,*asset,*effect,*companion,*transition;
    struct SceneInterpolation radius,x_motion,y_motion;
    void *overlay;
};
struct SceneDisplayShadow {
    u16 control;u8 unknown02[56];
    volatile u8 byte58,byte59;u8 unknown60[2];
    volatile u8 byte62,byte63;u8 unknown64[2];
    volatile u8 byte66;u8 unknown67;volatile u8 byte68;
};
extern struct SceneDisplayShadow gSceneDisplay;
extern const u8 gSceneVariantTransitionA[],gSceneVariantTransitionB[];
__asm__(".global gSceneVariantTransitionA\n.set gSceneVariantTransitionA,0x083A6B64\n.global gSceneVariantTransitionB\n.set gSceneVariantTransitionB,0x083A6B94");
extern const struct SceneCoordinatePair gSceneVariantCoordinates;
extern const u16 gSceneVariantXOffsets[2],gSceneVariantYOffsets[2];
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940\n.global gSceneVariantCoordinates\n.set gSceneVariantCoordinates,0x08149F94\n.global gSceneVariantXOffsets\n.set gSceneVariantXOffsets,0x08149F9C\n.global gSceneVariantYOffsets\n.set gSceneVariantYOffsets,0x08149FA0");
extern void *StartTransition(const void*,u32,void*) asm("RetailCall_080D7A70");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *CopySceneBytes(void*,const void*,u32) asm("RetailCall_081443FC");
extern void *PollTransition(void*) asm("RetailCall_080D7ABC");
extern u32 ConvertSceneCoordinates(s16,s16,s16*,s16*) asm("RetailCall_0801C960");
extern u32 LoadSceneResource(const void*,u32,u32,s16,s16,u32,u32) asm("RetailCall_080D72C8");
extern u32 SetSceneObjectPosition(u32,u32,u32,s16,s16) asm("RetailCall_080D49FC");
extern void *CreateSceneObject(u32,const void*,u32,u32) asm("RetailCall_080D4B64");
extern u32 SetSceneObjectEnabled(void*,u32) asm("RetailCall_0800BDA4");
extern u32 SetSceneObjectVariant(void*,u32) asm("RetailCall_0800BE10");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartSceneAsset(const void*,void*) asm("RetailCall_080D4704");
extern void *CreateSceneEffect(u32,u32,u32,void*) asm("RetailCall_080DAB84");
extern u32 SceneWindowMask(u32) asm("RetailCall_080035D0");
extern u32 SetSceneEffectMode(void*,u32) asm("RetailCall_080D9BA8");
extern u32 InitializeSceneInterpolation(struct SceneInterpolation*,s32,s32,s32) asm("RetailCall_080E0608");
extern void *CreateSceneCompanion(u32,u32,u32,const void*,void*) asm("RetailCall_080D979C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern u32 AdvanceSceneInterpolation(struct SceneInterpolation*) asm("RetailCall_080E064C");
extern u32 SetSceneEffectPosition(void*,s16,s16,u32) asm("RetailCall_080DAC40");
extern u32 MoveSceneObject(u32,s16,s16) asm("RetailCall_0800BC08");
extern u32 SceneInterpolationDone(struct SceneInterpolation*) asm("RetailCall_080E0690");
extern u32 PrepareSceneEffectEnd(void*) asm("RetailCall_080DADFC");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern void *PollSceneAsset(void*) asm("RetailCall_080D4774");
extern u32 RemoveSceneObject(void*,u32) asm("RetailCall_080D4D14");
extern u32 ClearSceneStage(void) asm("RetailCall_080D4020");
extern u32 SetDefinitionRecordFlag(void*,u32) asm("RetailCall_080DBEB4");
extern void *DeleteSceneEffect(void*) asm("RetailCall_080D9B64");
typedef char WorkSize[(sizeof(struct VariantSceneSequence)==76)?1:-1];
typedef char InterpolationSize[(sizeof(struct SceneInterpolation)==12)?1:-1];
u32 AdvanceVariantSceneSequence(void*,struct SceneContext*,struct VariantSceneSequence*) asm("OriginalSceneDefinitionQuestion_0011BB08");
u32 AdvanceVariantSceneSequence(void *owner,struct SceneContext *context,struct VariantSceneSequence *work)
{
    switch(context->state) {
    case 0: {
        u32 variant=context->definition_id-116;
        work->variant=variant;
        work->definition=context->definition;
        if(!(u8)variant)
            work->transition=StartTransition(gSceneVariantTransitionA,4,owner);
        else
            work->transition=StartTransition(gSceneVariantTransitionB,4,owner);
        break;
    }
    case 1:
        ResumeScene();
        break;
    case 256: {
        struct SceneCoordinatePair coordinates=gSceneVariantCoordinates;
        u16 x_offsets[2],y_offsets[2];
        void *transition;
        CopySceneBytes(x_offsets,gSceneVariantXOffsets,4);
        CopySceneBytes(y_offsets,gSceneVariantYOffsets,4);
        transition=PollTransition(work->transition);
        work->transition=transition;
        if(transition) break;
        ConvertSceneCoordinates(coordinates.values[work->variant].x,coordinates.values[work->variant].y,&work->x,&work->y);
        if(!work->variant)
            LoadSceneResource((void*)0x088F65D4,0,2,work->x,work->y,(u32)transition,1);
        else
            LoadSceneResource((void*)0x088F6620,0,2,work->x,work->y,(u32)transition,1);
        SetSceneObjectPosition(1,3,0,work->x,(s16)(work->y+12));
        work->object=CreateSceneObject(1,(void*)0x088F1B34,1015,7);
        SetSceneObjectEnabled(work->object,1);
        if(!work->variant) SetSceneObjectVariant(work->object,1);
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control|=mask;
            gSceneDisplay.control=control;
        }
        work->script=StartSceneScript((void*)0x0894DD98,owner);
        work->asset=StartSceneAsset((void*)0x0894C850,owner);
        work->effect=CreateSceneEffect(0,0,0,owner);
        gSceneDisplay.byte59=0;
        gSceneDisplay.byte58=0;
        gSceneDisplay.byte63=0;
        gSceneDisplay.byte62=160;
        gSceneDisplay.byte66=63;
        {
            u32 mask=SceneWindowMask(2);
            gSceneDisplay.byte68=63&~mask;
        }
        gSceneDisplay.control|=0x2000;
        SetSceneEffectMode(work->effect,1);
        InitializeSceneInterpolation(&work->radius,0,94,40);
        work->delay=60;
        InitializeSceneInterpolation(&work->x_motion,work->x,(s16)(work->x+x_offsets[work->variant]),80);
        InitializeSceneInterpolation(&work->y_motion,(s16)(work->y+12),(s16)(work->y+y_offsets[work->variant]+12),80);
        work->companion=CreateSceneCompanion(0,2,1,(void*)0x083A6BC4,owner);
        work->overlay=StartSceneOverlay((void*)0x083A6BD4,1,4,0,owner);
        context->state++;
        break;
    }
    case 257: {
        struct SceneInterpolation *radius=&work->radius;
        struct SceneInterpolation *x_motion,*y_motion;
        AdvanceSceneInterpolation(radius);
        SetSceneEffectPosition(work->effect,work->x,work->y,work->radius.value);
        if(work->delay) {
            work->delay--;
            if(work->delay) break;
        }
        x_motion=&work->x_motion;
        AdvanceSceneInterpolation(x_motion);
        y_motion=&work->y_motion;
        AdvanceSceneInterpolation(y_motion);
        MoveSceneObject(1,(s16)work->x_motion.value,(s16)work->y_motion.value);
        if(!(u8)SceneInterpolationDone(radius)) break;
        if(!(u8)SceneInterpolationDone(x_motion)) break;
        if(!(u8)SceneInterpolationDone(y_motion)) break;
        InitializeSceneInterpolation(radius,94,0,40);
        context->state++;
        break;
    }
    case 258: {
        struct SceneInterpolation *radius=&work->radius;
        void *asset;
        AdvanceSceneInterpolation(radius);
        PrepareSceneEffectEnd(work->effect);
        SetSceneEffectPosition(work->effect,work->x,work->y,work->radius.value);
        if(!(u8)SceneInterpolationDone(radius)) break;
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        asset=PollSceneAsset(work->asset);
        work->asset=asset;
        if(asset) break;
        RemoveSceneObject(work->object,1);
        work->object=asset;
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            control&=0xDFFF;
            gSceneDisplay.control=control;
        }
        ClearSceneStage();
        SetDefinitionRecordFlag(work->definition,1);
        work->script=StartSceneScript((void*)0x083A6BC8,owner);
        context->state++;
        break;
    }
    case 259:
        work->effect=DeleteSceneEffect(work->effect);
        if(work->effect) break;
        work->companion=DeleteSceneEffect(work->companion);
        if(work->companion) break;
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9");

__asm__(".global RetailCall_080035D0\n.thumb_set RetailCall_080035D0, 0x080035d1");

__asm__(".global RetailCall_0800BC08\n.thumb_set RetailCall_0800BC08, 0x0800bc09");

__asm__(".global RetailCall_0800BDA4\n.thumb_set RetailCall_0800BDA4, 0x0800bda5");

__asm__(".global RetailCall_0800BE10\n.thumb_set RetailCall_0800BE10, 0x0800be11");

__asm__(".global RetailCall_0801C960\n.thumb_set RetailCall_0801C960, 0x0801c961");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x080d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x080d3f09");

__asm__(".global RetailCall_080D4020\n.thumb_set RetailCall_080D4020, 0x080d4021");

__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x080d4705");

__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774, 0x080d4775");

__asm__(".global RetailCall_080D49FC\n.thumb_set RetailCall_080D49FC, 0x080d49fd");

__asm__(".global RetailCall_080D4B64\n.thumb_set RetailCall_080D4B64, 0x080d4b65");

__asm__(".global RetailCall_080D4D14\n.thumb_set RetailCall_080D4D14, 0x080d4d15");

__asm__(".global RetailCall_080D72C8\n.thumb_set RetailCall_080D72C8, 0x080d72c9");

__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x080d7a71");

__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x080d7abd");

__asm__(".global RetailCall_080D979C\n.thumb_set RetailCall_080D979C, 0x080d979d");

__asm__(".global RetailCall_080D9B64\n.thumb_set RetailCall_080D9B64, 0x080d9b65");

__asm__(".global RetailCall_080D9BA8\n.thumb_set RetailCall_080D9BA8, 0x080d9ba9");

__asm__(".global RetailCall_080DAB84\n.thumb_set RetailCall_080DAB84, 0x080dab85");

__asm__(".global RetailCall_080DAC40\n.thumb_set RetailCall_080DAC40, 0x080dac41");

__asm__(".global RetailCall_080DADFC\n.thumb_set RetailCall_080DADFC, 0x080dadfd");

__asm__(".global RetailCall_080DBEB4\n.thumb_set RetailCall_080DBEB4, 0x080dbeb5");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608, 0x080e0609");

__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C, 0x080e064d");

__asm__(".global RetailCall_080E0690\n.thumb_set RetailCall_080E0690, 0x080e0691");

__asm__(".global RetailCall_081443FC\n.thumb_set RetailCall_081443FC, 0x081443fd");
